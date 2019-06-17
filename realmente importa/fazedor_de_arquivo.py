import random
#cep + numero
#codigo_serie 
num_quartos = ['1', '2', '3', '4', '5', '6', '7']
num_banheiros = ['1', '2', '3', '4']
cor = ['roxo','vermelho','azul','amarelo','laranja','preto','branco','perola','rosa','verde','ambar','zaffre']
imobiliaria = ['Pague_mais_leve_menos','E_de_mentirinha', 'Estou_te_roubando', 'Trump_Towers', 'Corretissimo']
metros_quadrados = ['70', '90', '110', '130', '150', '170', '220', '500']
genero = ['casa','apartamento','geminado','bunker']
cep_numero = []
codigo_serie = []
#nao pode ter repetições

with open('banco_dados.txt','a') as the_file:
    for i in range(10000):
        n_quarto = random.randint(0,6)
        n_banheiro = random.randint(0,3)
        n_cor = random.randint(0,11)
        n_imobiliaria = random.randint(0,4)
        n_metros = random.randint(0,7)
        n_genero = random.randint(0,3)
        
        while True:
            cep = str(random.randint(11111111, 99999999))
            numero = str(random.randint(1000, 9999))
            cepNumero = cep + numero
            if cepNumero not in cep_numero:
                cep_numero.append(cepNumero)
                break
        while True:
            codigo = str(random.randint(1111111111, 9999999999))
            if codigo not in codigo_serie:
                codigo_serie.append(codigo)
                break 
        the_file.write(codigo + ' ' + cepNumero + ' ' + num_quartos[n_quarto] + ' ' + num_banheiros[n_banheiro] + ' ' + cor[n_cor] + ' ' + imobiliaria[n_imobiliaria] + ' ' + metros_quadrados[n_metros] + ' ' + genero[n_genero] + '\n')
the_file.close()