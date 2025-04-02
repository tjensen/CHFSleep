enum CHFSleep_Modifiers
{
    CHF_TIREDNESS = 1000
};

modded class ModifiersManager
{
    override void Init()
    {
        super.Init();

#ifdef SERVER
        AddModifier(new CHFTirednessModifier);
#endif // SERVER
    }
};

// vim:ft=enforce
