raw_input()
numbers = map(int, raw_input().split())
result = set(numbers)
print len(result)
result = map(str, sorted(result))
print ' '.join(result)