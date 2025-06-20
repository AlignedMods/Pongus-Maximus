#pragma once

class Menu {
public:
    virtual ~Menu() {}

    virtual void OnUpdate() {}
    virtual void OnRender() {}
};