import datetime

date = datetime.datetime(year=2000, month=1, day=1)
ans = 0
dic = [13, 1, 2, 3, 5, 4, 4, 2, 2, 2]

while date <= datetime.datetime(year=2024, month=4, day=13):
    dateStr = date.strftime('%Y%m%d')
    if sum([dic[i] for i in map(int, dateStr)]) > 50:
        ans += 1
    date += datetime.timedelta(days=1)

print(ans)
