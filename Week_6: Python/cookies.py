class Jar:
    def __init__(self,capacity = 12):
        self.size = self.set_size()

    def __str__(self):
        gnomm = ""
        cookie_no = size()
        for cookie in cookie_no:
            gnomm += "🍪"
        print(gnomm)

    @property
    def size(self):
        return self.size


    @size.setter
    def set_size(self,value = 0):
        return value



    @size.setter
    def deposit(self, n):
        cookie_number = self.size()
        if cookie_number + n > capacity:
            print("Too many (!) cookies were added to the jar")
            return ValueError
        else:
            if n == 1:
                print(f"{n} cookie added to the jar...")
            else:
                print(f"{n} cookies added to the jar...")
        self.number_of_cookies += n

    @size.setter
    def withdraw(self, n):
        cookie_number = self.size()
        if cookie_number - n < 0:
            print("As hungry as you were, you couldn't eat non-existent cookies")
            return ValueError
        else:
            if n == 1:
                print(f"{n} cookie vanished mysteriously from the jar...")
            else:
                print(f"{n} cookies vanished...")
        self.number_of_cookies -= n


    @property
    def capacity(self):
        return self.capacity






the_first_ever_cookie_jar = Jar()
c