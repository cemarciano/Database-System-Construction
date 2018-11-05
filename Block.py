from Record import *


class Block:
    def __init__(self, disk_name):
        """ Open disk file in write/read mode and set number of operations to 0 """
        self.disk = open(disk_name, "w+")  # Disk file
        self.n_r = 0  # Number of records
        self.max_size = 8  # Size of block
        self.n_op = 0  # Number of operations
        self.records = []  # List of records

    def __del__(self):
        self.persist(self.disk.tell())

    def persist(self, pos):
        self.n_r = 0
        self.n_op += 1
        self.disk.seek(pos)
        for record in self.records:
            self.disk.write(record)
        self.disk.flush()
        self.records = []
    # def write(self):
    # def read(self):
