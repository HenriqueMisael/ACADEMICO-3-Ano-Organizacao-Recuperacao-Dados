typedef struct {
    char *descricao;

    void (*executa)();
} ItemMenu;

typedef struct {
    ItemMenu *itens;
    int quantidade;
} Menu;

ItemMenu newItemMenu(const char *descricao, void (*executa)());
Menu *newMenu(int quantidade, ...);

void executaMenu(Menu *menu);