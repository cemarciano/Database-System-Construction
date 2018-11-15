from Record import *
from Block import *
from BTree import *


class Heap:
    def __init__(self, disk_name="Heap.cbd", indexBy=[], indexBTree=True):
        maxDegreeBTree = 5
        self.r_block = Block(disk_name)
        self.w_block = Block(disk_name)
        self.indexes = {}
        self.indexBTree = indexBTree
        for i in indexBy:
            if indexBTree:
                self.indexes.update({i:BTree(maxDegreeBTree)})
            else:
                self.indexes.update({i:{}})

    def insert(self, string):
        rec = Record(string)
        for i in self.indexes:
            if self.indexBTree:
                self.indexes[i].insert(getattr(rec,i))
                self.indexes[i].search(getattr(rec,i))[0].pos=self.w_block.disk.tell()
            else:
                self.indexes[i].update({getattr(rec,i):self.w_block.disk.tell()})
        self.w_block.write(self.w_block.disk.tell(), rec)

    def join(self, other_heap, field):
        pos, other_pos = 0, 0
        self.r_block.read(pos)
        while(self.r_block.records[0]):
            for i in self.r_block.records:
                if field in other_heap.indexes:  # if field is indexed
                    if other_heap.indexBTree:
                        other_heap.r_block.read(self.indexes[field].search(getattr(Record(i),field))[0].pos)
                    else:
                        other_heap.r_block.read(other_heap.indexes[field][getattr(Record(i), field)]*other_heap.r_block.record_size)
                    for j in other_heap.r_block.records:
                        if not j:
                            break
                        if getattr(Record(i), field) == getattr(Record(j), field):
                            print(i+"\n"+j+"\n")
                else:  # if field is NOT indexed
                    other_pos = 0
                    other_heap.r_block.read(other_pos)
                    while(other_heap.r_block.records[0]):
                        for j in other_heap.r_block.records:
                            if not j:
                                break
                            if getattr(Record(i), field) == getattr(Record(j), field):
                                print(i+"\n"+j+"\n")
                        other_pos += other_heap.r_block.max_size*other_heap.r_block.record_size
                        other_heap.r_block.read(other_pos)
            pos += self.r_block.max_size*self.r_block.record_size
            self.r_block.read(pos)


a = Heap("teste1.cbd")
a.insert("11111111111;54.037.661-5;estermoro@gmail.com;06/01/1952;Feminino;Yuri Matheus Antonia;5942.00")
a.insert("33333333333;54.037.661-5;estermoro@gmail.com;06/01/1952;Feminino;Yuri Matheus Antonia;5942.00")
b=Heap("teste2.cbd")
b.insert("22222222222;54.037.661-5;estermoro@gmail.com;06/01/1952;Feminino;Yuri Matheus Antonia;5942.00")

a.join(b, "nome")
