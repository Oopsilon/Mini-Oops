digraph G {
    node [shape = record];
    
    classes(`Object', `SmallInteger')
    
    isa(ObjectMetaCls, ObjectMetaCls);
    isa(ObjectCls, ObjectMetaCls);
    isa(SmallIntegerMetaCls, ObjectMetaCls);
    isa(SmallIntegerCls, SmallIntegerMetaCls);
    
    super(ObjectCls, nil);
    super(ObjectMetaCls, ObjectCls);
    super(SmallIntegerCls, ObjectCls);
    super(SmallIntegerMetaCls, ObjectMetaCls);
}
