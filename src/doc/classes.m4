digraph G {
    node [shape = record];
    
    class(Object);
    class(SmallInteger);
    
    isa(ObjectMetaCls, ObjectMetaCls);
    isa(ObjectCls, ObjectMetaCls);
    isa(SmallIntegerMetaCls, ObjectMetaCls);
    isa(SmallIntegerCls, SmallIntegerMetaCls);
    
    super(ObjectCls, nil);
    super(ObjectMetaCls, ObjectCls);
    super(SmallIntegerCls, ObjectCls);
    super(SmallIntegerMetaCls, ObjectMetaCls);
}
