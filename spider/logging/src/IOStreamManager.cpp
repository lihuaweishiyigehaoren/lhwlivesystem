

#include "IOStreamManager.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace logging {

std::vector<std::ostream*> IOStreamManager::GetDefaultOutputStreams(Severity severity)
{
    return _defaultOutputStreams[severity];
}

void IOStreamManager::SetOutputStream(std::ostream* outputStream, bool toManage)
{
    for ( auto outputStreamsPair : _defaultOutputStreams ) {
        _defaultOutputStreams[outputStreamsPair.first].push_back(outputStream);
    }

    if ( toManage ) {
        _managedStreams.insert(outputStream);
    }
}

void IOStreamManager::SetOutputStream(Severity severity, std::ostream* outputStream, bool toManage)
{
    _defaultOutputStreams[severity].push_back(outputStream);

    if ( toManage ) {
        _managedStreams.insert(outputStream);
    }
}

void IOStreamManager::SetOutputStream(std::vector<Severity> severities, std::ostream* outputStream, bool toManage)
{
    for ( Severity severity : severities ) {
        _defaultOutputStreams[severity].push_back(outputStream);
    }

    if ( toManage ) {
        _managedStreams.insert(outputStream);
    }
}

void IOStreamManager::SetOutputFile(const std::string& fileName)
{
    std::ostream* outputStream = CreateOutputFile(fileName);
    if ( !outputStream ) {
        return;
    }

    SetOutputStream(outputStream, true);
}

void IOStreamManager::SetOutputFile(Severity severity, const std::string& fileName)
{
    std::ostream* outputStream = CreateOutputFile(fileName);
    if ( !outputStream ) {
        return;
    }

    SetOutputStream(severity, outputStream, true);
}

void IOStreamManager::SetOutputFile(std::vector<Severity> severities, const std::string& fileName)
{
    std::ostream* outputStream = CreateOutputFile(fileName);
    if ( !outputStream ) {
        return;
    }

    SetOutputStream(severities, outputStream, true);
}

IOStreamManager& IOStreamManager::GetInstance()
{
    static IOStreamManager instance;

    return instance;
}

IOStreamManager::~IOStreamManager()
{
    for ( std::ostream* outputStream : _managedStreams ) {
        delete outputStream;
    }

    _managedStreams.clear();
}

IOStreamManager::IOStreamManager() :
    _defaultOutputStreams({
        { LOG_DEBUG, { &std::cout } },
        { LOG_INFO, { &std::cout } },
        { LOG_WARNING, { &std::cerr } },
        { LOG_ERROR, { &std::cerr } },
        { LOG_FATAL, { &std::cerr } }
    })
{
}

std::ostream* IOStreamManager::CreateOutputFile(const std::string& fileName)
{
    // Initialize file stream
    std::ofstream* fileStream = new std::ofstream();
    std::ios_base::openmode mode = std::ios_base::out;
    mode |= std::ios_base::trunc;
    fileStream->open(fileName, mode);

    // Error handling
    if (!fileStream->is_open()) {
        // Print error information
        std::ostringstream ss_error;
        ss_error << "FATAL ERROR:  could not Open log file: [" << fileName << "]";
        ss_error << "\n\t\t std::ios_base state = " << fileStream->rdstate();
        std::cerr << ss_error.str().c_str() << std::endl << std::flush;

        // Cleanup
        fileStream->close();
        delete fileStream;
        fileStream = nullptr;
    }

    return fileStream;
}

}
