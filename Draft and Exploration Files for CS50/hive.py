#Number of babies
#Number of workers
#Winter (kills workers)

"""
Grow babies (Increase number of babies)
Babies transform into workers (Subtract number of babies from workers)

"""

import math

class Hive:
    def __init__(self,grubs,workers,max_no_workers=500,):
        self.max_no_workers = max_no_workers
        self.workers = workers
        self.grubs = grubs
        #self._grubs = int(input("Enter number of grubs: "))
        #self._workers = int(input("Enter number of workers: "))

    @property
    def workers():
        return self._workers


    @workers.setter
    def workers(self,value):
        if value < self.max_no_workers:
            self._workers = value
            print(f"Stats: workers: {self._workers}\n")
        else:
            print("Max no workers reached...")
            raise ValueError


    @property
    def grubs():
        print(f"Stats: \n grubs: {self._grubs} \n workers: {self._workers}\n")
        return self._grubs

    @grubs.setter
    def grubs(self,value):
        if value <= self._workers / 2:
            self._grubs = value
            print(f"Stats: \n grubs: {self._grubs} \n workers: {self._workers}\n")
        else:
            print("Too many grubs vs worker bees (should be less than half the number of worker bees)")
            raise ValueError


    def get_Grubs(self):
        print(f"Grubs: {self._grubs}")
        return self._grubs

    def get_Workers(self):
        print(f"Workers: {self._workers}")
        return self._grubs

    def march(self,value):
        if value <= self._workers:
            proportional_death = ((self._workers - value) / self._workers) / 2
            self._workers -= value
            self._grubs = math.trunc(self._grubs * proportional_death)
            print(f"Stats: \n grubs: {self._grubs} \n workers: {self._workers}\n")

        else:
            print(f"End stats: \n grubs: {self._grubs} \n workers: {self._workers}\n")

            print("The bee colony was wiped out...")
            raise ValueError

    def grow_Grubs(self,value):
        if value <= self._grubs:
            if self._workers + value < self.max_no_workers:
                self._workers += value
                self._grubs -= value
                print(f"Stats: \n grubs: {self._grubs} \n workers: {self._workers}\n")
            else:
                print("Growth would exceed max capacity of hive")
        else:
            print(f"Stats: \n grubs: {self._grubs} \n workers: {self._workers}\n")
            print("Too many grubs tried to develop...")


my_hive = Hive(5,10)
print(my_hive.get_Workers())
print(my_hive.get_Grubs())
my_hive.march(15)






