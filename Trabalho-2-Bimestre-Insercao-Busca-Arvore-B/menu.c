#include <malloc.h>
#include <zconf.h>
#include "menu.h"
#include "util.h"

ItemMenu newItemMenu(const char *descricao, void (*executa)()) {
    ItemMenu *item = (ItemMenu *) malloc(sizeof(ItemMenu));

    item->descricao = descricao;
    item->executa = executa;

    return *item;
}

Menu *newMenu(int quantidade, ...) {
    Menu *menu = (Menu *) malloc(sizeof(Menu));
    menu->quantidade = quantidade;
    menu->itens = (ItemMenu *) malloc(quantidade * sizeof(ItemMenu));

    va_list itens;

    va_start(itens, quantidade);

    for (int i = 0; i < quantidade; i++) {
        menu->itens[i] = va_arg(itens, ItemMenu);
    }

    va_end(itens);

    return menu;
}

void executaMenu(Menu *menu) {

    println("Escolha uma opcao para executar pelo numero:");

    for (int i = 0; i < menu->quantidade; i++) {
        printf("%d - %s\n", i, menu->itens[i].descricao);
    }

    do {
        println("> ");

        int option = readInt();
        if (option < 0 || option >= menu->quantidade) {
            println("Opcao invalida!");
        } else {
            menu->itens[option].executa();
            break;
        }
    } while (TRUE);
}
