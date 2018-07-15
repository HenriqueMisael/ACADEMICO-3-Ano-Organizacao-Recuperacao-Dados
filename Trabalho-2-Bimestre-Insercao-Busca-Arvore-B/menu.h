#ifndef TRABALHO_2_BIMESTRE_INSERCAO_BUSCA_ARVORE_B_MENU_H
#define TRABALHO_2_BIMESTRE_INSERCAO_BUSCA_ARVORE_B_MENU_H
typedef struct {
    char *descricao;
    void (*executa)();
} ItemMenu;

typedef struct {
    ItemMenu *itens;
    int quantidade;
} Menu;

ItemMenu newItemMenu(char *descricao, void (*executa)());

Menu *newMenu(int quantidade, ...);

void executaMenu(Menu *menu);

#endif //TRABALHO_2_BIMESTRE_INSERCAO_BUSCA_ARVORE_B_MENU_H