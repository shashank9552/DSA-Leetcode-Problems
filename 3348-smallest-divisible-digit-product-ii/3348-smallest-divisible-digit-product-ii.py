from functools import lru_cache

class Solution:
    def smallestNumber(self, num: str, t: int) -> str:
        # factorize t
        need = [0] * 4
        primes = [2, 3, 5, 7]
        x = t
        for i, p in enumerate(primes):
            while x % p == 0:
                need[i] += 1
                x //= p
        if x != 1:
            return "-1"

        contrib = {
            1: (0, 0, 0, 0),
            2: (1, 0, 0, 0),
            3: (0, 1, 0, 0),
            4: (2, 0, 0, 0),
            5: (0, 0, 1, 0),
            6: (1, 1, 0, 0),
            7: (0, 0, 0, 1),
            8: (3, 0, 0, 0),
            9: (0, 2, 0, 0),
        }

        n = len(num)

        # prefix prime contributions
        pref = [[0] * 4 for _ in range(n + 1)]
        zero_pos = n
        for i, ch in enumerate(num):
            pref[i + 1] = pref[i].copy()
            d = int(ch)
            if d == 0 and zero_pos == n:
                zero_pos = i
            if d:
                c = contrib[d]
                for j in range(4):
                    pref[i + 1][j] += c[j]

        def remain_after_prefix(idx):
            return [
                max(0, need[j] - pref[idx][j])
                for j in range(4)
            ]

        @lru_cache(None)
        def can_fill(length, a, b, c, d):
            if length == 0:
                return a == b == c == d == 0
            # simple pruning
            if a > 3 * length:
                return False
            if b > 2 * length:
                return False
            if c > length:
                return False
            if d > length:
                return False

            for dig in range(1, 10):
                da, db, dc, dd = contrib[dig]
                na = max(0, a - da)
                nb = max(0, b - db)
                nc = max(0, c - dc)
                nd = max(0, d - dd)
                if can_fill(length - 1, na, nb, nc, nd):
                    return True
            return False

        def build_suffix(length, rem):
            a, b, c, d = rem
            ans = []
            for _ in range(length):
                for dig in range(1, 10):
                    da, db, dc, dd = contrib[dig]
                    na = max(0, a - da)
                    nb = max(0, b - db)
                    nc = max(0, c - dc)
                    nd = max(0, d - dd)
                    if can_fill(length - len(ans) - 1, na, nb, nc, nd):
                        ans.append(str(dig))
                        a, b, c, d = na, nb, nc, nd
                        break
            return "".join(ans)

        # check current number
        if zero_pos == n:
            rem = remain_after_prefix(n)
            if rem == [0, 0, 0, 0]:
                return num

        # same length
        for i in range(n - 1, -1, -1):
            if i > zero_pos:
                continue

            prefix = pref[i]

            start = int(num[i]) + 1 if i < zero_pos else 1
            if start == 10:
                continue

            for dig in range(start, 10):
                if dig == 0:
                    continue
                cur = [
                    prefix[k] + contrib[dig][k]
                    for k in range(4)
                ]
                rem = [
                    max(0, need[k] - cur[k])
                    for k in range(4)
                ]
                if can_fill(n - i - 1, *rem):
                    return (
                        num[:i]
                        + str(dig)
                        + build_suffix(n - i - 1, rem)
                    )

        # longer length
        L = n + 1
        while True:
            if can_fill(L, *need):
                return build_suffix(L, need)
            L += 1
            # impossible to require more than these exponents
            if L > n + 60:
                return "-1"