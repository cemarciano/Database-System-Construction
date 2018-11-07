from Record import *
from Block import *


class Heap:
    def __init__(self, disk_name="Heap.cbd"):
        self.r_block = Block(disk_name)
        self.w_block = Block(disk_name)

    def insert(self, string):
        rec = Record(string)
        self.w_block.write(self.w_block.disk.tell(), rec)

    def join(self,other_heap,field):
        pos, other_pos=0,0
        self.r_block.read(pos)
        while(self.r_block.records[0]!=''):
            for i in self.r_block.records:
                other_heap.r_block.read(other_pos)
                while(other_heap.r_block.records[0]!=''):
                    for j in other_heap.r_block.records:
                        if j=='':
                            break
                        if getattr(Record(i),field)==getattr(Record(j),field):
                            print(i+"\n"+j+"\n")
                    other_pos+=other_heap.r_block.max_size*other_heap.r_block.record_size
                    other_heap.r_block.read(other_pos)
            pos+=self.r_block.max_size*self.r_block.record_size
            self.r_block.read(pos)
