#include "ContactListener.hpp"

void ContactListener::BeginContact(b2Contact *contact)
{
    b2Body *a = contact->GetFixtureA()->GetBody();
    b2Body *b = contact->GetFixtureB()->GetBody();

    auto *data_a = reinterpret_cast<void *>(a->GetUserData().pointer);
    auto *data_b = reinterpret_cast<void *>(b->GetUserData().pointer);

    Player *player = nullptr;

    if (dynamic_cast<Player *>((Player *)data_a))
    {
        player = (Player *)data_a;
    }
    else if (dynamic_cast<Player *>((Player *)data_b))
    {
        player = (Player *)data_b;
    }

    if (player)
    {
        player->setIsGrounded(true);
    }
}

void ContactListener::EndContact(b2Contact *contact)
{
    b2Body *a = contact->GetFixtureA()->GetBody();
    b2Body *b = contact->GetFixtureB()->GetBody();

    auto *data_a = reinterpret_cast<void *>(a->GetUserData().pointer);
    auto *data_b = reinterpret_cast<void *>(b->GetUserData().pointer);

    Player *player = nullptr;

    if (dynamic_cast<Player *>((Player *)data_a))
    {
        player = (Player *)data_a;
    }
    else if (dynamic_cast<Player *>((Player *)data_b))
    {
        player = (Player *)data_b;
    }

    if (player)
    {
        // player->setIsGrounded(false);
    }
}