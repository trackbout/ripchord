#pragma once

//==============================================================================
namespace Keyboard
{
    //==============================================================================
    static inline bool isBlackKey (const int inNoteNumber)
    {
        div_t keyDiv = div (inNoteNumber, 12);
        int keyInOctave = keyDiv.rem;

        if ((keyInOctave == 1) ||
            (keyInOctave == 3) ||
            (keyInOctave == 6) ||
            (keyInOctave == 8) ||
            (keyInOctave == 10))
        {
            return true;
        }

        return false;
    }

    //==============================================================================
    static inline int getWhiteNoteIndex (int inNote)
    {
        std::map<int, int> whiteNoteIndexes;

        whiteNoteIndexes[21] = 0;
        whiteNoteIndexes[23] = 1;
        whiteNoteIndexes[24] = 2;
        whiteNoteIndexes[26] = 3;
        whiteNoteIndexes[28] = 4;
        whiteNoteIndexes[29] = 5;
        whiteNoteIndexes[31] = 6;
        whiteNoteIndexes[33] = 7;
        whiteNoteIndexes[35] = 8;
        whiteNoteIndexes[36] = 9;
        whiteNoteIndexes[38] = 10;
        whiteNoteIndexes[40] = 11;
        whiteNoteIndexes[41] = 12;
        whiteNoteIndexes[43] = 13;
        whiteNoteIndexes[45] = 14;
        whiteNoteIndexes[47] = 15;
        whiteNoteIndexes[48] = 16;
        whiteNoteIndexes[50] = 17;
        whiteNoteIndexes[52] = 18;
        whiteNoteIndexes[53] = 19;
        whiteNoteIndexes[55] = 20;
        whiteNoteIndexes[57] = 21;
        whiteNoteIndexes[59] = 22;
        whiteNoteIndexes[60] = 23;
        whiteNoteIndexes[62] = 24;
        whiteNoteIndexes[64] = 25;
        whiteNoteIndexes[65] = 26;
        whiteNoteIndexes[67] = 27;
        whiteNoteIndexes[69] = 28;
        whiteNoteIndexes[71] = 29;
        whiteNoteIndexes[72] = 30;
        whiteNoteIndexes[74] = 31;
        whiteNoteIndexes[76] = 32;
        whiteNoteIndexes[77] = 33;
        whiteNoteIndexes[79] = 34;
        whiteNoteIndexes[81] = 35;
        whiteNoteIndexes[83] = 36;
        whiteNoteIndexes[84] = 37;
        whiteNoteIndexes[86] = 38;
        whiteNoteIndexes[88] = 39;
        whiteNoteIndexes[89] = 40;
        whiteNoteIndexes[91] = 41;
        whiteNoteIndexes[93] = 42;
        whiteNoteIndexes[95] = 43;
        whiteNoteIndexes[96] = 44;
        whiteNoteIndexes[98] = 45;
        whiteNoteIndexes[100] = 46;
        whiteNoteIndexes[101] = 47;
        whiteNoteIndexes[103] = 48;
        whiteNoteIndexes[105] = 49;
        whiteNoteIndexes[107] = 50;
        whiteNoteIndexes[108] = 51;

        return whiteNoteIndexes.at (inNote);
    }

    //==============================================================================
    static inline int getBlackNoteIndex (int inNote)
    {
        std::map<int, int> blackNoteIndexes;

        blackNoteIndexes[22] = 0;
        blackNoteIndexes[25] = 1;
        blackNoteIndexes[27] = 2;
        blackNoteIndexes[30] = 3;
        blackNoteIndexes[32] = 4;
        blackNoteIndexes[34] = 5;
        blackNoteIndexes[37] = 6;
        blackNoteIndexes[39] = 7;
        blackNoteIndexes[42] = 8;
        blackNoteIndexes[44] = 9;
        blackNoteIndexes[46] = 10;
        blackNoteIndexes[49] = 11;
        blackNoteIndexes[51] = 12;
        blackNoteIndexes[54] = 13;
        blackNoteIndexes[56] = 14;
        blackNoteIndexes[58] = 15;
        blackNoteIndexes[61] = 16;
        blackNoteIndexes[63] = 17;
        blackNoteIndexes[66] = 18;
        blackNoteIndexes[68] = 19;
        blackNoteIndexes[70] = 20;
        blackNoteIndexes[73] = 21;
        blackNoteIndexes[75] = 22;
        blackNoteIndexes[78] = 23;
        blackNoteIndexes[80] = 24;
        blackNoteIndexes[82] = 25;
        blackNoteIndexes[85] = 26;
        blackNoteIndexes[87] = 27;
        blackNoteIndexes[90] = 28;
        blackNoteIndexes[92] = 29;
        blackNoteIndexes[94] = 30;
        blackNoteIndexes[97] = 31;
        blackNoteIndexes[99] = 32;
        blackNoteIndexes[102] = 33;
        blackNoteIndexes[104] = 34;
        blackNoteIndexes[106] = 35;

        return blackNoteIndexes.at (inNote);
    }

    //==============================================================================
    static inline int getWhiteNoteNumber (int inIndex)
    {
        std::map<int, int> whiteNoteNumbers;

        whiteNoteNumbers[0] = 21;
        whiteNoteNumbers[1] = 23;
        whiteNoteNumbers[2] = 24;
        whiteNoteNumbers[3] = 26;
        whiteNoteNumbers[4] = 28;
        whiteNoteNumbers[5] = 29;
        whiteNoteNumbers[6] = 31;
        whiteNoteNumbers[7] = 33;
        whiteNoteNumbers[8] = 35;
        whiteNoteNumbers[9] = 36;
        whiteNoteNumbers[10] = 38;
        whiteNoteNumbers[11] = 40;
        whiteNoteNumbers[12] = 41;
        whiteNoteNumbers[13] = 43;
        whiteNoteNumbers[14] = 45;
        whiteNoteNumbers[15] = 47;
        whiteNoteNumbers[16] = 48;
        whiteNoteNumbers[17] = 50;
        whiteNoteNumbers[18] = 52;
        whiteNoteNumbers[19] = 53;
        whiteNoteNumbers[20] = 55;
        whiteNoteNumbers[21] = 57;
        whiteNoteNumbers[22] = 59;
        whiteNoteNumbers[23] = 60;
        whiteNoteNumbers[24] = 62;
        whiteNoteNumbers[25] = 64;
        whiteNoteNumbers[26] = 65;
        whiteNoteNumbers[27] = 67;
        whiteNoteNumbers[28] = 69;
        whiteNoteNumbers[29] = 71;
        whiteNoteNumbers[30] = 72;
        whiteNoteNumbers[31] = 74;
        whiteNoteNumbers[32] = 76;
        whiteNoteNumbers[33] = 77;
        whiteNoteNumbers[34] = 79;
        whiteNoteNumbers[35] = 81;
        whiteNoteNumbers[36] = 83;
        whiteNoteNumbers[37] = 84;
        whiteNoteNumbers[38] = 86;
        whiteNoteNumbers[39] = 88;
        whiteNoteNumbers[40] = 89;
        whiteNoteNumbers[41] = 91;
        whiteNoteNumbers[42] = 93;
        whiteNoteNumbers[43] = 95;
        whiteNoteNumbers[44] = 96;
        whiteNoteNumbers[45] = 98;
        whiteNoteNumbers[46] = 100;
        whiteNoteNumbers[47] = 101;
        whiteNoteNumbers[48] = 103;
        whiteNoteNumbers[49] = 105;
        whiteNoteNumbers[50] = 107;
        whiteNoteNumbers[51] = 108;

        return whiteNoteNumbers.at (inIndex);
    }

    //==============================================================================
    static inline int getBlackNoteNumber (int inIndex)
    {
        std::map<int, int> blackNoteNumbers;

        blackNoteNumbers[0] = 22;
        blackNoteNumbers[1] = 25;
        blackNoteNumbers[2] = 27;
        blackNoteNumbers[3] = 30;
        blackNoteNumbers[4] = 32;
        blackNoteNumbers[5] = 34;
        blackNoteNumbers[6] = 37;
        blackNoteNumbers[7] = 39;
        blackNoteNumbers[8] = 42;
        blackNoteNumbers[9] = 44;
        blackNoteNumbers[10] = 46;
        blackNoteNumbers[11] = 49;
        blackNoteNumbers[12] = 51;
        blackNoteNumbers[13] = 54;
        blackNoteNumbers[14] = 56;
        blackNoteNumbers[15] = 58;
        blackNoteNumbers[16] = 61;
        blackNoteNumbers[17] = 63;
        blackNoteNumbers[18] = 66;
        blackNoteNumbers[19] = 68;
        blackNoteNumbers[20] = 70;
        blackNoteNumbers[21] = 73;
        blackNoteNumbers[22] = 75;
        blackNoteNumbers[23] = 78;
        blackNoteNumbers[24] = 80;
        blackNoteNumbers[25] = 82;
        blackNoteNumbers[26] = 85;
        blackNoteNumbers[27] = 87;
        blackNoteNumbers[28] = 90;
        blackNoteNumbers[29] = 92;
        blackNoteNumbers[30] = 94;
        blackNoteNumbers[31] = 97;
        blackNoteNumbers[32] = 99;
        blackNoteNumbers[33] = 102;
        blackNoteNumbers[34] = 104;
        blackNoteNumbers[35] = 106;

        return blackNoteNumbers.at (inIndex);
    }

    //==============================================================================
    static inline String getNoteNameFromNumber (int inNoteNumber)
    {
        std::map<int, String> noteNames;

        noteNames[21] = "A0";
        noteNames[22] = "A#0";
        noteNames[23] = "B0";
        noteNames[24] = "C1";
        noteNames[25] = "C#1";
        noteNames[26] = "D1";
        noteNames[27] = "D#1";
        noteNames[28] = "E1";
        noteNames[29] = "F1";
        noteNames[30] = "F#1";
        noteNames[31] = "G1";
        noteNames[32] = "G#1";
        noteNames[33] = "A1";
        noteNames[34] = "A#1";
        noteNames[35] = "B1";
        noteNames[36] = "C2";
        noteNames[37] = "C#2";
        noteNames[38] = "D2";
        noteNames[39] = "D#2";
        noteNames[40] = "E2";
        noteNames[41] = "F2";
        noteNames[42] = "F#2";
        noteNames[43] = "G2";
        noteNames[44] = "G#2";
        noteNames[45] = "A2";
        noteNames[46] = "A#2";
        noteNames[47] = "B2";
        noteNames[48] = "C3";
        noteNames[49] = "C#3";
        noteNames[50] = "D3";
        noteNames[51] = "D#3";
        noteNames[52] = "E3";
        noteNames[53] = "F3";
        noteNames[54] = "F#3";
        noteNames[55] = "G3";
        noteNames[56] = "G#3";
        noteNames[57] = "A3";
        noteNames[58] = "A#3";
        noteNames[59] = "B3";
        noteNames[60] = "C4";
        noteNames[61] = "C#4";
        noteNames[62] = "D4";
        noteNames[63] = "D#4";
        noteNames[64] = "E4";
        noteNames[65] = "F4";
        noteNames[66] = "F#4";
        noteNames[67] = "G4";
        noteNames[68] = "G#4";
        noteNames[69] = "A4";
        noteNames[70] = "A#4";
        noteNames[71] = "B4";
        noteNames[72] = "C5";
        noteNames[73] = "C#5";
        noteNames[74] = "D5";
        noteNames[75] = "D#5";
        noteNames[76] = "E5";
        noteNames[77] = "F5";
        noteNames[78] = "F#5";
        noteNames[79] = "G5";
        noteNames[80] = "G#5";
        noteNames[81] = "A5";
        noteNames[82] = "A#5";
        noteNames[83] = "B5";
        noteNames[84] = "C6";
        noteNames[85] = "C#6";
        noteNames[86] = "D6";
        noteNames[87] = "D#6";
        noteNames[88] = "E6";
        noteNames[89] = "F6";
        noteNames[90] = "F#6";
        noteNames[91] = "G6";
        noteNames[92] = "G#6";
        noteNames[93] = "A6";
        noteNames[94] = "A#6";
        noteNames[95] = "B6";
        noteNames[96] = "C7";
        noteNames[97] = "C#7";
        noteNames[98] = "D7";
        noteNames[99] = "D#7";
        noteNames[100] = "E7";
        noteNames[101] = "F7";
        noteNames[102] = "F#7";
        noteNames[103] = "G7";
        noteNames[104] = "G#7";
        noteNames[105] = "A7";
        noteNames[106] = "A#7";
        noteNames[107] = "B7";
        noteNames[108] = "C8";

        return noteNames.at (inNoteNumber);
    }
}
