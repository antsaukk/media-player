#include <QApplication>
#include "media_player.h"
#include "tester.h"
#include <cstring>

int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath("plugins");
    QApplication a(argc, argv);
    media_player w;
    w.show();

    if (argc >= 2 && std::strcmp(argv[1], "test") == 0) {
        Tester tester = Tester(&w);
        tester.run_tests();
    }

    return a.exec();
}
