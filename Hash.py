from Record import *
from Block import *
from BTree import *
from bplustree import BPlusTree, StrSerializer #pip install btreeplus
#see https://github.com/NicolasLM/bplustree
from os import getcwd
from sys import byteorder

class Hash:
    def __init__(self, disk_name="Hash.cbd", indexBy=[], indexBTree=True, indexBPlusTree=False):
        maxDegreeBTree = 10
        self.r_block = Block(disk_name)
        self.w_block = Block(disk_name)
        self.indexes={}
        self.indexBTree = indexBTree
        self.indexBPlusTree = indexBPlusTree
        self.hashedPositions = []
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
        self.w_block.write(abs(hash(rec.cpf)//10**6)*self.w_block.max_size*self.w_block.record_size, rec)
        self.w_block.persist(abs(hash(rec.cpf)//10**6)*self.w_block.max_size*self.w_block.record_size)
        self.hashedPositions += [abs(hash(rec.cpf)//10**6)*self.w_block.max_size*self.w_block.record_size]
        for i in self.indexes:
            if self.indexBPlusTree:
                self.indexes[i].insert(getattr(rec,i),abs(hash(rec.cpf)//10**6)*self.w_block.max_size*self.w_block.record_size.to_bytes(4,byteorder),True) #True for replacing node, if already existant
            else:
                if self.indexBTree:
                    self.indexes[i].insert(getattr(rec,i))
                    self.indexes[i].search(getattr(rec,i))[0].pos=abs(hash(rec.cpf)//10**6)*self.w_block.max_size*self.w_block.record_size
                else:
                    self.indexes[i].update({getattr(rec,i):abs(hash(rec.cpf)//10**6)*self.w_block.max_size*self.w_block.record_size})

    def join(self,other_hash,field,other_field=""):
        if not other_field:
            other_field=field
        for pos in self.hashedPositions:
            self.r_block.read(pos)
            for i in self.r_block.records:
                if i=='\x00'*self.r_block.record_size or not i:
                    break
                if field=="cpf": #if field is primary key cpf
                    other_hash.r_block.read(abs(hash(Record(i).cpf)//10**6)*self.w_block.max_size*self.w_block.record_size)
                    if other_hash.r_block.records[0]!='\x00'*self.r_block.record_size:
                        print(i+"\n"+str(other_hash.r_block.records[0])+"\n")
                else:
                    if other_field in other_hash.indexes: #if field is indexed
                        if other_hash.indexBPlusTree:
                            other_hash.r_block.read(int.from_bytes(other_hash.indexes[other_field].get(getattr(Record(i),field),byteorder)))
                        else:
                            if other_hash.indexBTree:
                                other_hash.r_block.read(other_hash.indexes[other_field].search(getattr(Record(i),field))[0].pos)
                            else:
                                other_hash.r_block.read(other_hash.indexes[other_field][getattr(Record(i),field)])
                        for j in other_hash.r_block.records:
                            if not j:
                                break
                            if getattr(Record(i),field)==getattr(Record(j),other_field):
                                print(i+"\n"+j+"\n")
                    else:
                        other_pos = 0
                        other_hash.r_block.read(other_pos)
                        while(other_hash.r_block.records[0]):
                            for j in other_hash.r_block.records:
                                if j=='\x00'*other_hash.r_block.record_size or not j:
                                    break
                                if getattr(Record(i), field) == getattr(Record(j), other_field):
                                    print(i+"\n"+j+"\n")
                            other_pos += other_hash.r_block.max_size*other_hash.r_block.record_size
                            other_hash.r_block.read(other_pos)

#a=Hash("teste1.cbd",indexBy=["nome"])
#a.insert("11111111111;54.037.661-5;estermoro@gmail.com;06/01/1952;Feminino;Yuri Matheus Antonia;5942.00")
#b=Hash("teste2.cbd",indexBy=["nome"])
#b.insert("11111111111;54.037.661-5;estermoro@gmail.com;06/01/1952;Feminino;Yuri Matheus Antonia;5942.00")
#a.join(b,"cpf")

#del a, b
