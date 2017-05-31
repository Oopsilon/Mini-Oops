/* Oopsilon
 * Context class definition.
 *
 *      Copyright Notice
 *
 * Copyright (c) 2017 D. Mackay. All rights reserved.
 *
 * This file and its contents are supplied under the terms of the Peer
 * Production Licence as found in the Oopsilon project's source repository,
 * and David Mackay is the sole copyright holder.
 *
 *      End Copyright Notice
 */

class ContextDesc : MemDesc
<contextOop> pfp;

<methodOop> method;
    
<objVecOop<oop>::type> environment;
    
<std::vector<oop *>> args;
<std::vector<oop *>> temps;
<std::vector<oop *>> stack;
    
<smiOop> pc;

end