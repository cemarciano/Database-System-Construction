class Record:
    def __init__(self, string):
        """ Split argument (record) by ; character and set member variables """
        # set splited record
        field = string.split(';')
        # set cpf
        self.cpf = field[0]
        # set rg
        self.rg = field[1]
        # set email
        self.email = field[2] + '\0' * \
            (40 - len(field[2])) if len(field[2]) < 40 else field[2][:40]
        # set data de nascimento
        self.nasc = field[3]
        # set sexo
        self.sexo = field[4] + '\0' * \
            (9 - len(field[4])) if len(field[4]) < 9 else field[4][:9]
        # set nome
        self.nome = field[5] + '\0'*(40 - len(field[5])
                                     ) if len(field[5]) < 40 else field[5][:40]
        # set salario
        self.salario = field[6] + '\0' * \
            (10 - len(field[6])) if len(field[6]) < 10 else field[6][:10]

    def __str__(self):
        """ Return all member variables concatenated """
        return self.cpf+";"+self.rg+";"+self.email+";"+self.nasc+";"+self.sexo+";"+self.nome+";"+self.salario
