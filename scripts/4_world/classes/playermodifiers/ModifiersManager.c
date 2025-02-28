enum CHFSleep_Modifiers
{
    CHF_TIREDNESS = 1000
};

modded class ModifiersManager
{
    override void Init()
    {
        super.Init();
        AddModifier(new CHFTirednessModifier);
    }
};

// vim:ft=enforce
