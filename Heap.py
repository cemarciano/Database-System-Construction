from Record import *
from Block import *


class Heap:
    def __init__(self, disk_name="Heap.cbd", indexBy=[]):
        self.r_block = Block(disk_name)
        self.w_block = Block(disk_name)
        self.indexes = {}
        for i in indexBy:
            self.indexes.update({i: open(i+"_"+disk_name, "w+")})

    def __del__(self):
        for i in self.indexes:
            self.indexes[i].close()

    def insert(self, string):
        rec = Record(string)
        for i in self.indexes:
            self.indexes[i].write(getattr(rec, i)+" " +
                                  str(self.w_block.disk.tell())+"\n")
            self.indexes[i].flush()
        self.w_block.write(self.w_block.disk.tell(), rec)

    def join(self, other_heap, field):
        pos, other_pos = 0, 0
        self.r_block.read(pos)
        while(self.r_block.records[0]):
            for i in self.r_block.records:
                if field in other_heap.indexes:  # if field is indexed
                    for line in other_heap.indexes[field]:
                        if getattr(Record(i), field) == line.split()[0]:
                            other_heap.r_block.read(line.split()[1]*other_heap.r_block.record_size)
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