from Record import *
from Block import *
from BTree import *

class Hash:
    def __init__(self, disk_name="Hash.cbd", indexBy=[], indexBTree=True):
        maxDegreeBTree = 5
        self.r_block = Block(disk_name)
        self.w_block = Block(disk_name)
        self.indexes={}
        self.indexBTree = indexBTree
        for i in indexBy:
            if indexBTree:
                self.indexes.update({i:BTree(maxDegreeBTree)})
            else:
                self.indexes.update({i:{}})

    def insert(self, string):
        rec = Record(string)
        self.w_block.write(abs(hash(rec.cpf)//10**6)*self.w_block.max_size*self.w_block.record_size, rec)
        self.w_block.persist(abs(hash(rec.cpf)//10**6)*self.w_block.max_size*self.w_block.record_size)
        for i in self.indexes:
            if self.indexBTree:
                self.indexes[i].insert(getattr(rec,i))
                self.indexes[i].search(getattr(rec,i))[0].pos=abs(hash(rec.cpf)//10**6)*self.w_block.max_size*self.w_block.record_size
            else:
                self.indexes[i].update({getattr(rec,i):abs(hash(rec.cpf)//10**6)*self.w_block.max_size*self.w_block.record_size})

    def join(self,other_hash,field,other_field=""):
        if not other_field:
            other_field=field
        pos=0
        self.r_block.read(pos)
        while(self.r_block.records[0]):
            for i in self.r_block.records:
                if i=='\x00'*self.r_block.record_size or not i:
                    break
                if field=="cpf": #if field is primary key cpf
                    other_hash.r_block.read(abs(hash(Record(i).cpf)//10**6)*self.w_block.max_size*self.w_block.record_size)
                    if other_hash.r_block.records[0]!='\x00'*self.r_block.record_size:
                        print(i+"\n"+str(other_hash.r_block.records[0])+"\n")
                else:
                    if other_field in other_hash.indexes: #if field is indexed
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
                        print("The requested field is not supported yet.")
                        return
            pos+=self.r_block.max_size*self.r_block.record_size
            self.r_block.read(pos)

a=Hash("teste1.cbd")
a.insert("11111111111;54.037.661-5;estermoro@gmail.com;06/01/1952;Feminino;Yuri Matheus Antonia;5942.00")
b=Hash("teste2.cbd")
b.insert("11111111111;54.037.661-5;estermoro@gmail.com;06/01/1952;Feminino;Yuri Matheus Antonia;5942.00")
a.join(b,"cpf")
