

/*************************************************************************
 *                                                                       *
 * Voce                                                                  *
 * Copyright (C) 2005                                                    *
 * Tyler Streeter  tylerstreeter@gmail.com                               *
 * All rights reserved.                                                  *
 * Web: voce.sourceforge.net                                             *
 *                                                                       *
 * This library is free software; you can redistribute it and/or         *
 * modify it under the terms of EITHER:                                  *
 *   (1) The GNU Lesser General Public License as published by the Free  *
 *       Software Foundation; either version 2.1 of the License, or (at  *
 *       your option) any later version. The text of the GNU Lesser      *
 *       General Public License is included with this library in the     *
 *       file license-LGPL.txt.                                          *
 *   (2) The BSD-style license that is included with this library in     *
 *       the file license-BSD.txt.                                       *
 *                                                                       *
 * This library is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the files    *
 * license-LGPL.txt and license-BSD.txt for more details.                *
 *                                                                       *
 *************************************************************************/

#include <voce/voce.h>
#include "myVoce/CommandParser.h"
#include <unistd.h>
#include <ros/package.h>

/// A sample application showing how to use Voce's speech synthesis 
/// capabilities.

int main(int argc, char **argv)
{
    std::string path = ros::package::getPath("voice_recognition");
    path.append("/resources");
    std::cout << path << std::endl;
    
    voce::init("/opt/voce/lib", false, true, path, "islurp");

    std::cout << "Voice initialize" << std::endl;

    bool quit = false;
    bool started = false;
    
    
    
    
    while (!quit)
    {
        // Normally, applications would do application-specific things 
        // here.  For this sample, we'll just sleep for a little bit.

        usleep(200);

        while (voce::getRecognizerQueueSize() > 0)
        {
                    
            std::string s = voce::popRecognizedString();
                        
                        
            // Check if the string contains 'quit'.
            if (std::string::npos != s.rfind("quit"))
            {
                quit = true;
                break;
            }
          
            if (s == "end voice")
            {
                started = false;
                std::cout << "Voice Recognition stopped!"<< std::endl;
                break;
                
            }
            else if (s == "start voice")
            {
                std::cout << "Voice Recognition started!"<< std::endl;
                started = true;
            }
            else if (started)
            {
                
                
                 boost::to_upper(s);

                 std::cout << "TEST: " << s << std::endl;

                 CommandParser p;
                 p.parse(s);
                 

                std::cout << "You said ----------: " << s << std::endl;
            } 

            //voce::synthesize(s);
                        
        }//while (voce::getRecognizerQueueSize() > 0)
    }//while (!quit))

    voce::destroy();
    return 0;
}