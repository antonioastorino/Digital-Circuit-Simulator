//
//  DCSMemoryProgrammer.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 22/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSMemoryProgrammer_hpp
#define DCSMemoryProgrammer_hpp

class DCSMemoryProgrammer {
private:
	DCSRam16x8 *memory;
public:
	DCSMemoryProgrammer() = delete;
	DCSMemoryProgrammer(DCSRam16x8 *memory);
	
	void program(ushort address, ushort value);
};

#endif /* DCSMemoryProgrammer_hpp */
