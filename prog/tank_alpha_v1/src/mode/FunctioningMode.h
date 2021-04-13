// Author: John-William Lebel, 2021-04-08, creation

// a class that reprensents the current mode we're operating in

#ifndef FUNCTIONING_MODE_H
    #define FUNCTIONING_MODE_H
    
    #define LISTENING_TO_YOUR_COMMANDS_FUNCTIONING_MODE                       0
    #define SWARM_IS_SWARMY_FUNCTIONING_MODE                                  1
    
    class FunctioningMode
    {
        public:
            static void execute();
            
        private:
            static unsigned char _functioningMode;
    };

#endif
