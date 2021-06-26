// La fonction main .

int main()
{
    CURRENT  instance;
    switch(init())
    {
        case 0 :
            {
                init_Instance(&instance);
                Save_Instance(&instance);
                break;
            }
        case 1 :
            Load_Instance(&instance);
            break;
    }
    Game(&instance);
    return 0;
}

