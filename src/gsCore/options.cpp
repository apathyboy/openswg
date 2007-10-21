/**
 * Galaxy Open-Source Massively Multiplayer Game Simulation Engine
 * Copyright (C) 2007 OpenSWG Team <http://www.openswg.com>
 */

// *********************************************************************
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// To read the license please visit http://www.gnu.org/copyleft/gpl.html
// *********************************************************************

#include <fstream>

#include <gsCore/options.h>

namespace gsCore
{
    
    Options::Options()
    {}

    void Options::setVisibleOptions(boost::program_options::options_description options)
    {
        m_visibleOptions.add(options);
    }

    boost::program_options::options_description Options::getVisibleOptions()
    {
        return m_visibleOptions;
    }

    void Options::setCommandLineOptions(boost::program_options::options_description options)
    {
        m_commandLineOptions.add(options);
    }

    boost::program_options::options_description Options::getCommandLineOptions()
    {
        return m_commandLineOptions;
    }

    void Options::setConfigFileOptions(boost::program_options::options_description options)
    {
        m_configFileOptions.add(options);
    }

    boost::program_options::options_description Options::getConfigFileOptions()
    {
        return m_configFileOptions;
    }

    void Options::parseCommandLine(int argc, char *argv[])
    {
        try
        {
            boost::program_options::store(boost::program_options::command_line_parser(argc, argv).
                options(m_commandLineOptions).run(), m_variablesMap);
        }
        catch(std::exception& e)
        {
            printf("%s\n", e.what());
        } 
    }

    void Options::parseConfigFile(const std::string& filename)
    {
        try
        {
            std::ifstream fileStream(filename.c_str());
            boost::program_options::store(boost::program_options::parse_config_file(fileStream, m_configFileOptions), m_variablesMap);
        }
        catch(std::exception& e)
        {
            printf("%s\n", e.what());
        } 
    }

    boost::program_options::variables_map Options::getParsedOptions()
    {
        return m_variablesMap;
    }
}

