#ifndef OBJETS_H_INCLUDE
#define OBJETS_H_INCLUDED

void creerMenu()
{
    int idaffichage = glutCreateMenu(menuAffichage);
    glutAddMenuEntry("Grille    G",1);
    glutAddMenuEntry("Repere    R",2);

    int idMode = glutCreateMenu(menuMenu);
    glutAddMenuEntry("Sommet",1);
    glutAddMenuEntry("Filaire",2);
    glutAddMenuEntry("Grille",3);

    int idArp = glutCreateMenu(menuArp);
    glutAddMenuEntry("Noire",1);
    glutAddMenuEntry("Gris",2);
    glutAddMenuEntry("Blanc",3);

    int idPrincipale = glutCreateMenu(menuPrincipale);
    glutAddSubMenu("Affichage",idaffichage);
    glutAddSubMenu("Mode",idMode);
    glutAddSubMenu("Arrier plan",idArp);
    glutAddMenuEntry("Quitter   Q",0);
    // associer la fonction pour le button droit de la souris
    glutAttachMenu(GLUT_RIGHT_BUTTON);

}


#endif // OBJETS_H_INCLUDED
