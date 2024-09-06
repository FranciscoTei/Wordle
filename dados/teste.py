import unicodedata

print("Teste de acentuação:")
def remover_acentos(texto):
    """Remove acentos de um texto."""
    return ''.join(c for c in unicodedata.normalize('NFKD', texto) if not unicodedata.combining(c))

def processar_arquivo(entrada, saida):
    """Remove acentos de todas as linhas de um arquivo e salva em outro arquivo."""
    try:
        with open(entrada, 'r', encoding='utf-8') as arquivo_entrada, \
             open(saida, 'w', encoding='utf-8') as arquivo_saida:
            
            for linha in arquivo_entrada:
                linha_sem_acentos = remover_acentos(linha)
                arquivo_saida.write(linha_sem_acentos)
        
        print(f"Arquivo '{entrada}' processado com sucesso e salvo como '{saida}'.")
    
    except FileNotFoundError:
        print(f"Erro: O arquivo '{entrada}' não foi encontrado.")
    except IOError as e:
        print(f"Erro de I/O: {e}")

# Definindo os nomes dos arquivos
entrada = 'lista_completa.txt'
saida = 'lista_sem_acentos.txt'

# Processando o arquivo
print(f"Processando arquivo '{entrada}'...")
processar_arquivo(entrada, saida)
