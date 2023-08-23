class Jar:
    def __init__(self, capacity=12):
        self._size = 0
        self.capacity = capacity

    def __str__(self):
        for i in range(self._size):
            print("🍪")

    def deposit(self, n):
        if self._size + n > self.capacity:
            print(f"The cookie jar is rammed full - you cannot add {n} more cookies...")
        else:
            self._size += n

    def withdraw(self, n):
        if self._size - n < 0:
            print(f"The cookie jar is looking empty - you cannot take {n} more cookies...")
        else:
            self.size -= n

    @property
    def capacity(self):
        return self._capacity


    @capacity.setter
    def capacity(self, value):
        if value < 0:
            print("Capacity cannot be negative")
            raise ValueError
        self._capacity = value

    @property
    def size(self):
        return self._size

    @size.setter
    def size(self,value):
        if  0 > value:
            print("Jar is initialised with a negative number of cookies or a number which exceeds max no. (12)")
            raise ValueError
        elif value > self.capacity:
            print("The jar cannot carry this many cookies")
            raise ValueError
        else:
            self._size = value

cookie_jar = Jar()
cookie_jar = Jar()
cookie_jar.deposit(11)
cookie_jar.__str__()
cookie_jar.withdraw(5)
print("Second attempt")
cookie_jar.__str__()
cookie_jar.deposit(5)
cookie_jar.__str__()
cookie_jar.deposit(14)
max = cookie_jar.capacity
print(max)



