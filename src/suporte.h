
/**
 * @struct MensagemSuporte
 * @brief Estrutura para armazenar informações de uma mensagem de suporte.
 *
 * Esta estrutura contém os seguintes campos:
 * - nome: Nome do usuario logado.
 * - email: Endereço de email do usuario.
 * - mensagem: Conteúdo da mensagem de suporte.
 * - data_hora: Data em que a mensagem foi enviada.
 */
typedef struct {
    char nome[100];
    char email[100];
    char mensagem[500];
    char data_hora[50];
} MensagemSuporte;

/**
 * @struct NoMensagemSuporte
 * @brief Estrutura para armazenar um nó de uma lista encadeada de mensagens de suporte.
 *
 * Esta estrutura contém os seguintes campos:
 * - mensagem: Mensagem de suporte armazenada no nó.
 * - proximo: Ponteiro para o próximo nó da lista.
 */
struct MensagemSuporteNo {
    MensagemSuporte mensagem;
    struct MensagemSuporteNo* proximo;
};


/**
 * @struct NoMensagemSuporte
 * @brief Estrutura para armazenar um nó de uma lista encadeada de mensagens de suporte.
 *
 * Esta estrutura contém os seguintes campos:
 * - mensagem: Mensagem de suporte armazenada no nó.
 * - proximo: Ponteiro para o próximo nó da lista.
 */
typedef struct MensagemSuporteNo NoMensagemSuporte;

/**
 * @brief Envia uma mensagem de suporte.
 *
 * Esta função é responsável por enviar uma mensagem de suporte para o sistema.
 * Pode ser utilizada para relatar problemas, solicitar ajuda ou fornecer feedback.
 *
 * @note Certifique-se de que todos os parâmetros necessários estejam configurados
 * corretamente antes de chamar esta função.
 */
void enviarMensagemSuporte();


/**
 * @brief Cria um novo nó de mensagem de suporte.
 *
 * Esta função aloca memória para um novo nó de mensagem de suporte e inicializa
 * o nó com a mensagem fornecida.
 *
 * @param mensagem A mensagem de suporte a ser armazenada no novo nó.
 * @return Um ponteiro para o novo nó de mensagem de suporte.
 */
NoMensagemSuporte* novoNoMensagemSuporte(MensagemSuporte mensagem);

/**
 * @brief Imprime as mensagens de suporte contidas em uma lista.
 *
 * Esta função percorre a lista encadeada de mensagens de suporte e imprime
 * cada mensagem na saída padrão.
 *
 * @param lista Ponteiro para o início da lista encadeada de mensagens de suporte.
 */
void imprimirMensagensSuporte(NoMensagemSuporte* lista);

/**
 * @brief Carrega as mensagens de suporte.
 *
 * Esta função lê as mensagens de suporte de um arquivo ou outra fonte de dados
 * e as carrega em uma estrutura de dados apropriada.
 *
 * @return Um ponteiro para a estrutura NoMensagemSuporte contendo as mensagens carregadas.
 */
NoMensagemSuporte* carregarMensagensSuporte();