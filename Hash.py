from Record import *
from Block import *

class Hash:
    def __init__(self, disk_name="Hash.cbd"):
        self.r_block = Block(disk_name)
        self.w_block = Block(disk_name)

    def insert(self, string):
        rec = Record(string)
        self.w_block.write(abs(hash(rec.cpf)//10**6), rec)
        self.w_block.persist(abs(hash(rec.cpf)//10**6))

