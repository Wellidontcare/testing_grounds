class Counter:
    count = 0
    num = 0
    def __init__(self, num):
        Counter.count += 1
        self.num = num


def main():
    counter_list = [Counter(x) for x in range(10)]
    for x in counter_list:
        print(x.num())

if __name__ == "__main__":
    main()