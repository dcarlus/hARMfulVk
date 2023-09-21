// TestApp.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <geometry/points/Point3Df.hpp>
#include <entities/EntityFactory.hpp>
#include <components/ComponentFactory.hpp>

class TransformComponent : public Bane::Component {
    private:
        Mind::Point3Df m_position;

    public:
        TransformComponent(Bane::Entity& entity)
            : Bane::Component(Bane::Component::Quantity::One, entity) {}

        void setPosition(const Mind::Point3Df& position) { m_position = position; }
        void setPosition(const float x, const float y, const float z) { m_position.set(x, y, z); }

        const Mind::Point3Df& position() const { return m_position; }
};

int main()
{
    std::cout << "Hello World!\n";

    Bane::EntityFactory entityFactory;
    auto entity1 = entityFactory.create();
    std::cout << "Create Entity #" << entity1.id() << "\n";

    Bane::ComponentFactory<TransformComponent> transformFactory;
    auto transform1 = transformFactory.createComponentFor(entity1);
    std::cout << "Create TransformComponent " << transform1 -> position() << " for Entity #" << transform1 -> entityID() << "\n";
    std::cout << "There are " << transformFactory.count() << " components in the app now!\n";
    transformFactory.destroyComponentsOf(entity1);
    std::cout << "Destroy components of Entity #" << entity1.id() << "\n";
    std::cout << "There are " << transformFactory.count() << " components in the app now!\n";
    entityFactory.destroy(entity1);
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
