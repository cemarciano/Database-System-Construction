from Record import *
from Block import *
from BTree import *
from bplustree import BPlusTree, StrSerializer #pip install btreeplus
#see https://github.com/NicolasLM/bplustree
from os import getcwd
from sys import byteorder


class Heap:
    def __init__(self, disk_name="Heap.cbd", indexBy=[], indexBTree=True, indexBPlusTree=False):
        maxDegreeBTree = 10
        self.r_block = Block(disk_name)
        self.w_block = Block(disk_name)
        self.indexes = {}
        self.indexBTree = indexBTree
        self.indexBPlusTree = indexBPlusTree
        for i in indexBy:
            if indexBPlusTree:
                self.indexes.update({i:BPlusTree(getcwd()+"\\"+i+".index",serializer=StrSerializer(),key_size=128)})
            else:
                if indexBTree:
                    self.indexes.update({i:BTree(maxDegreeBTree)})
                else:
                    self.indexes.update({i:{}})

    def __del__(self):
        if self.indexBPlusTree:
            for i in indexBy:
                self.indexes[i].close()

    def insert(self, string):
        rec = Record(string)
        for i in self.indexes:
            if self.indexBPlusTree:
                self.indexes[i].insert(getattr(rec,i),self.w_block.disk.tell().to_bytes(4,byteorder),True) #True for replacing node, if already existant
            else:
                if self.indexBTree:
                    self.indexes[i].insert(getattr(rec,i))
                    self.indexes[i].search(getattr(rec,i))[0].pos=self.w_block.disk.tell()
                else:
                    self.indexes[i].update({getattr(rec,i):self.w_block.disk.tell()})
        self.w_block.write(self.w_block.disk.tell(), rec)

    def join(self, other_heap, field, other_field=""):
        if not other_field:
            other_field=field
        pos, other_pos = 0, 0
        self.r_block.read(pos)
        while(self.r_block.records[0]):
            for i in self.r_block.records:
                if not i:
                    break
                if other_field in other_heap.indexes:  # if field is indexed
                    if other_heap.indexBPlusTree:
                        other_heap.r_block.read(int.from_bytes(other_heap.indexes[other_field].get(getattr(Record(i),field),byteorder)))
                    else:
                        if other_heap.indexBTree:
                            other_heap.r_block.read(other_heap.indexes[other_field].search(getattr(Record(i),field))[0].pos)
                        else:
                            other_heap.r_block.read(other_heap.indexes[other_field][getattr(Record(i), field)]*other_heap.r_block.record_size)
                    for j in other_heap.r_block.records:
                        if not j:
                            break
                        if getattr(Record(i), field) == getattr(Record(j), other_field):
                            print(i+"\n"+j+"\n")
                else:  # if field is NOT indexed
                    other_pos = 0
                    other_heap.r_block.read(other_pos)
                    while(other_heap.r_block.records[0]):
                        for j in other_heap.r_block.records:
                            if not j:
                                break
                            if getattr(Record(i), field) == getattr(Record(j), other_field):
                                print(i+"\n"+j+"\n")
                        other_pos += other_heap.r_block.max_size*other_heap.r_block.record_size
                        other_heap.r_block.read(other_pos)
            pos += self.r_block.max_size*self.r_block.record_size
            self.r_block.read(pos)


#a=Heap("teste1.cbd",indexBy=["nome"])
#a.insert("11111111111;54.037.661-5;estermoro@gmail.com;06/01/1952;Feminino;Yuri Matheus Antonia;5942.00")
#a.insert("33333333333;54.037.661-5;estermoro@gmail.com;06/01/1952;Feminino;Yuri Matheus Antonia;5942.00")
#b=Heap("teste2.cbd",indexBy=["nome"])
#b.insert("22222222222;54.037.661-5;estermoro@gmail.com;06/01/1952;Feminino;Yuri Matheus Antonia;5942.00")

#a.w_block.persist(0) #debug-only
#b.w_block.persist(0) #debug-only

#a.join(b, "nome")

#del a, b
