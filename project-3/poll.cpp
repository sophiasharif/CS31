#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

// Return true if argument is a two-uppercase-letter state code, or false otherwise
bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
        "LA.ME.MA.MD.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
        "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2 &&
            stateCode.find('.') == string::npos &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos); // match found
}

// Return true if argument is a valid state forecast, or false otherwise
bool isValidStateForecast(string stateForecast)
{

    const int LEN = stateForecast.size();

    // edge case - state forecast does not at least contain a state
    if (LEN < 2)
        return false;

    // check there are only digits and letters in the string - no spaces or special chars
    for (int i = 0; i != LEN; i++)
    {
        char c = stateForecast.at(i);
        if (!(isdigit(c) || isalpha(c)))
        {
            return false;
        }
    }

    // check state code is valid
    string stateCode = "";
    stateCode += toupper(stateForecast.at(0));
    stateCode += toupper(stateForecast.at(1));
    if (!isValidUppercaseStateCode(stateCode))
        return false;

    // check the last char is a letter so counter loop below does not go out of bounds
    if (!isalpha(stateForecast.at(LEN - 1)))
        return false;

    // check each party result is valid
    // if arg is just a state, this loop will not execute
    for (int i = 2; i < LEN; i++)
    {
        // check the next char is digit and that there are no more than two digits
        int counter = 0;
        for (; isdigit(stateForecast.at(i)); i++, counter++)
            ;
        if (counter == 0 || counter > 2)
            return false;
        // check there is exactly one letter after nums, check next char is a digit
        if (!isalpha(stateForecast.at(i)) || (i + 1 < LEN && !isdigit(stateForecast.at(i + 1))))
            return false;
    }
    return true;
}

// Return true if argument is a valid poll string, or false otherwise
bool isValidPollString(string pollData)
{

    const int LEN = pollData.size();

    // edge case - no forecasts in data
    if (LEN == 0)
        return true;

    // if first and last char are not letters, return false
    if (!(isalpha(pollData.at(0)) && isalpha(pollData.at(LEN - 1))))
        return false;

    for (int i = 0; i < LEN; i++)
    {
        string stateForecast = "";
        // add everything before the next comma to stateForecast & increment i
        for (; (i < LEN) && (pollData.at(i) != ','); stateForecast += pollData.at(i), i++)
            ;
        // check if valid state forecast
        if (!isValidStateForecast(stateForecast))
            return false;
    }
    return true;
}

// Return how many votes the input party won in the input state forecast.
int processStateForecast(string stateForecast, char party)
{

    int totalSeats = 0;

    // iterate through chars and check if they are equal to c
    for (int i = 2; i != stateForecast.size(); i++)
    {
        if (tolower(stateForecast.at(i)) == tolower(party))
        {
            if (isdigit(stateForecast.at(i - 2)))
                // add two digit num to totalSeats
                totalSeats += stoi(stateForecast.substr(i - 2, 2));
            else
                // add one digit num to totalSeats
                totalSeats += stoi(stateForecast.substr(i - 1, 1));
        }
    }
    // if no matches, return -1
    return totalSeats;
}

// Save how many seats the party won in the input poll data string into seatCount.
// returns 1 if invalid poll string, 2 if invalid party, 0 if success.
int countSeats(string pollData, char party, int &seatCount)
{

    // pollData is not a poll data string, return 1
    if (!isValidPollString(pollData))
        return 1;

    // If party is not a letter, return 2
    if (!isalpha(party))
        return 2;

    // Set seatCount to the total number of seats that pollData predicts the party indicated by party will win, then return 0
    int tally = 0;
    const int LEN = pollData.size();

    // iterate through state forecasts and add to tally
    for (int i = 0; i < LEN; i++)
    {
        string stateForecast = "";
        // add everything before the next comma to stateForecast & increment i
        for (; (i < LEN) && (pollData.at(i) != ','); stateForecast += pollData.at(i), i++);
        // add to tally
        tally += processStateForecast(stateForecast, party);
    }

    seatCount = tally;

    return 0;
}

int main()
{
    // TEST CASES FOR isValidStateForecast

        // VALID GIVEN FORECASTS
        assert(isValidStateForecast("CT5D"));
        assert(isValidStateForecast("ne3r00D"));
        assert(isValidStateForecast("NY9R16D1I"));
        assert(isValidStateForecast("NJ3D5R4D"));
        assert(isValidStateForecast("VT"));

        // INVALID FORECASTS
        assert(!isValidStateForecast("KS 4R"));     // space in middle
        assert(!isValidStateForecast("ga4 r"));     // space in middle
        assert(!isValidStateForecast("nj 43d"));    // space in middle
        assert(!isValidStateForecast("ma43f6 3f")); // space in middle
        assert(!isValidStateForecast(" ga4r"));     // space at start
        assert(!isValidStateForecast("ga4r "));     // space at end
        assert(!isValidStateForecast("m34f45r"));   // invalid state code
        assert(!isValidStateForecast("mg32d"));     // invalid state code
        assert(!isValidStateForecast("wa3/34f"));   // includes special character
        assert(!isValidStateForecast("wa2"));       // last party result is invalid
        assert(!isValidStateForecast("ca3f32"));    // last party result is invalid
        assert(!isValidStateForecast("mD3d3/"));    // last party result is invalid
        assert(!isValidStateForecast(""));          // empty string
        assert(!isValidStateForecast(" "));         // just a space
        assert(!isValidStateForecast("m"));         // single letter

    // TEST CASES FOR isValidPollString

        // VALID POLL STRINGS
        assert(isValidPollString("CT5D,NY9R16D1I,VT,ne3r00D"));
        assert(isValidPollString("cA"));
        assert(isValidPollString("ca,wa,md"));
        assert(isValidPollString("cA3d5r34w,ny5g23h6h,vt"));
        assert(isValidPollString(""));
        assert(isValidPollString("CT"));
        assert(isValidPollString("ct"));

        // INVALID POLL STRINGS
        assert(!isValidPollString(" "));                             // just a space
        assert(!isValidPollString("m"));                             // one letter
        assert(!isValidPollString(",CT5D,NY9R16D1I,VT,ne3r00D"));    // first char is comma
        assert(!isValidPollString("ca,"));                           // last char is comma
        assert(!isValidPollString("T5D,NY9R16D1I,VT,ne3r00"));       // ends in digit
        assert(!isValidPollString("CT5D,NY9R16D1I,VT,ne3r00D, ca")); // contains space
        assert(!isValidPollString("CT5D,NY9R16D1I,,VT,ne3r00D"));    // two commas in a row
        assert(!isValidPollString(","));                             // just a comma
  

    // TEST CASES FOR processStateForecast
        assert(processStateForecast("ca5d4d", 'd') == 9);
        assert(processStateForecast("ca50d4d", 'd') == 54);
        assert(processStateForecast("ca4r4i", 'd') == 0);
        assert(processStateForecast("ca4d4D", 'd') == 8); // mixed upper & lower letters
        assert(processStateForecast("ca", 'd') == 0);     // no party results at all

    // TEST CASES FOR countSeats
        int seats = -999;
        assert(countSeats("ca32d", '/', seats) == 2); assert(seats == -999);  // invalid party
        assert(countSeats("cf32d", 'd', seats) == 1); assert(seats == -999);// invalid poll string
        assert(countSeats("ca4d4D", 'D', seats) == 0); assert(seats == 8); // two D parties
        assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", 'D', seats) == 0); assert(seats == 21);
        assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", 'r', seats) == 0); assert(seats == 12);
        assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", 'i', seats) == 0); assert(seats == 1);
        assert(countSeats("", 'D', seats) == 0); assert(seats == 0);
    
    cerr << "All tests succeeded!" << endl;

}
