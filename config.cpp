class CfgPatches
{
    class CHFSleep
    {
        requiredAddons[]=
        {
            "DZ_Scripts",
            "DZ_Sounds_Effects",
            "JM_CF_Scripts"
        };
    };
};

class CfgMods
{
    class CHFSleep
    {
        type="mod";
        defines[] = {"ZenSleep"};
        inputs="chfsleep/data/inputs.xml";
        dependencies[]=
        {
            "Game",
            "World",
            "Mission"
        };
        class defs
        {
            class gameScriptModule
            {
                value="";
                files[]=
                {
                    "chfsleep/scripts/3_game"
                };
            };
            class worldScriptModule
            {
                value="";
                files[]=
                {
                    "chfsleep/scripts/4_world"
                };
            };
            class missionScriptModule
            {
                value="";
                files[]=
                {
                    "chfsleep/scripts/5_mission"
                };
            };
        };
    };
};

// TODO: Make sure all yawn sounds are equalized volume-wise
class CfgSoundShaders // Sound effect definitions
{
    class baseCharacter_SoundShader;
    // Male yawns
    class yawn1_Male_SoundShader : baseCharacter_SoundShader
    {
        samples[] = { {"chfsleep\data\sounds\yawn1_m",1} };
        volume = 1;
        range = 30;
        rangeCurve[] = { {0,1},{0.5,0.7},{1,0} };
    };
    class yawn2_Male_SoundShader : baseCharacter_SoundShader
    {
        samples[] = { {"chfsleep\data\sounds\yawn2_m",1} };
        volume = 1;
        range = 30;
        rangeCurve[] = { {0,1},{0.5,0.7},{1,0} };
    };
    class yawn3_Male_SoundShader : baseCharacter_SoundShader
    {
        samples[] = { {"chfsleep\data\sounds\yawn3_m",1} };
        volume = 1;
        range = 30;
        rangeCurve[] = { {0,1},{0.5,0.7},{1,0} };
    };
    // Female yawns
    class yawn1_Female_SoundShader : baseCharacter_SoundShader
    {
        samples[] = { {"chfsleep\data\sounds\yawn1_f",1} };
        volume = 1;
        range = 30;
        rangeCurve[] = { {0,1},{0.5,0.7},{1,0} };
    };
    class yawn2_Female_SoundShader : baseCharacter_SoundShader
    {
        samples[] = { {"chfsleep\data\sounds\yawn2_f",1} };
        volume = 1;
        range = 30;
        rangeCurve[] = { {0,1},{0.5,0.7},{1,0} };
    };
    class yawn3_Female_SoundShader : baseCharacter_SoundShader
    {
        samples[] = { {"chfsleep\data\sounds\yawn3_f",1} };
        volume = 1;
        range = 30;
        rangeCurve[] = { {0,1},{0.5,0.7},{1,0} };
    };
    // Male sleep sounds
    class sleep1_Male_SoundShader : baseCharacter_SoundShader
    {
        samples[] = { {"chfsleep\data\sounds\sleep1_m",1} };
        volume = 1;
        range = 30;
        rangeCurve[] = { {0,1},{0.5,0.7},{1,0} };
    };
    class sleep2_Male_SoundShader : baseCharacter_SoundShader
    {
        samples[] = { {"chfsleep\data\sounds\sleep2_m",1} };
        volume = 1;
        range = 30;
        rangeCurve[] = { {0,1},{0.5,0.7},{1,0} };
    };
    class sleep3_Male_SoundShader : baseCharacter_SoundShader
    {
        samples[] = { {"chfsleep\data\sounds\sleep3_m",1} };
        volume = 1;
        range = 30;
        rangeCurve[] = { {0,1},{0.5,0.7},{1,0} };
    };
    // Female sleep sounds
    class sleep1_Female_SoundShader : baseCharacter_SoundShader
    {
        samples[] = { {"chfsleep\data\sounds\sleep1_f",1} };
        volume = 1;
        range = 30;
        rangeCurve[] = { {0,1},{0.5,0.7},{1,0} };
    };
    class sleep2_Female_SoundShader : baseCharacter_SoundShader
    {
        samples[] = { {"chfsleep\data\sounds\sleep2_f",1} };
        volume = 1;
        range = 30;
        rangeCurve[] = { {0,1},{0.5,0.7},{1,0} };
    };
    class sleep3_Female_SoundShader : baseCharacter_SoundShader
    {
        samples[] = { {"chfsleep\data\sounds\sleep3_f",1} };
        volume = 1;
        range = 30;
        rangeCurve[] = { {0,1},{0.5,0.7},{1,0} };
    };
};

class CfgSoundSets // Sound effect definitions
{
    class baseCharacter_SoundSet;
    // Male yawns
    class yawn1_Male_SoundSet : baseCharacter_SoundSet
    {
        soundShaders[] = { "yawn1_Male_SoundShader" };
    };
    class yawn2_Male_SoundSet : baseCharacter_SoundSet
    {
        soundShaders[] = { "yawn2_Male_SoundShader" };
    };
    class yawn3_Male_SoundSet : baseCharacter_SoundSet
    {
        soundShaders[] = { "yawn3_Male_SoundShader" };
    };
    // Female yawns
    class yawn1_Female_SoundSet : baseCharacter_SoundSet
    {
        soundShaders[] = { "yawn1_Female_SoundShader" };
    };
    class yawn2_Female_SoundSet : baseCharacter_SoundSet
    {
        soundShaders[] = { "yawn2_Female_SoundShader" };
    };
    class yawn3_Female_SoundSet : baseCharacter_SoundSet
    {
        soundShaders[] = { "yawn3_Female_SoundShader" };
    };
    // Male sleep sounds
    class sleep1_Male_SoundSet : baseCharacter_SoundSet
    {
        soundShaders[] = { "sleep1_Male_SoundShader" };
    };
    class sleep2_Male_SoundSet : baseCharacter_SoundSet
    {
        soundShaders[] = { "sleep2_Male_SoundShader" };
    };
    class sleep3_Male_SoundSet : baseCharacter_SoundSet
    {
        soundShaders[] = { "sleep3_Male_SoundShader" };
    };
    // Female sleep sounds
    class sleep1_Female_SoundSet : baseCharacter_SoundSet
    {
        soundShaders[] = { "sleep1_Female_SoundShader" };
    };
    class sleep2_Female_SoundSet : baseCharacter_SoundSet
    {
        soundShaders[] = { "sleep2_Female_SoundShader" };
    };
    class sleep3_Female_SoundSet : baseCharacter_SoundSet
    {
        soundShaders[] = { "sleep3_Female_SoundShader" };
    };
};

class CfgSoundEffects
{
    class AttenuationsEffects
    {
        // Flashbang attenuation. TODO: Spend way too many hours playing with this instead of doing something productive.
        // Ideas: Increase attenuation and wacky sleep effects if player is very tired / has been sleeping a long time?
        class ZenSleepAttenuation
        {
            class Equalizer0
            {
                center[] = { 196,2000,8367,10000 };
                bandwidth[] = { 2,2,0.1,2 };
                gain[] = { 1.4125376,0.12589253,1.9952624,0.12589253 };
            };
            class Equalizer1
            {
                center[] = { 60,1000,2000,10000 };
                bandwidth[] = { 2,1,0.1,2 };
                gain[] = { 1,0.3548134,0.25118864,0.12589253 };
            };
            class Echo
            {
                WetDryMix = 0.25;
                Feedback = 0.2;
                Delay = 50;
            };
        };
    };
};
