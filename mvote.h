#ifndef MVOTERUNNERDEF
#define MVOTERUNNERDEF
    /*
    *  Read records from file voterfp to system
    *
    *  @param system The system to insert results into
    *  @param voterfp A pointer to the file from which we get data
    */
    void readRecordsFromFile(MVoteSystem* system, FILE* voterfp);

#endif
