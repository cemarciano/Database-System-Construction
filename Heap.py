from Record import *
from Block import *


class Heap:
    def __init__(self, disk_name="Heap.cbd"):
        self.r_block = Block(disk_name)
        self.w_block = Block(disk_name)

    def insert(self, string):
        rec = Record(string)
        self.w_block.write(self.w_block.disk.tell(), rec)
