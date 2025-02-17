/*
 * Parser.h
 */

#ifndef PARSER_H
#define PARSER_H

class Circuit;
class LibraryHandler;

/**
 * Yal-Parser. This class parses *.yal files and imports them into
 * the graph data base. Supported formats: YAL.
 */
class Parser {
public:
    static void parse(int argc, const char** argv, Circuit* circuit, const int debugLevel = 0);
};

#endif // PARSER_H
