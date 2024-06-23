Notes:
    "Not included" means that the given flag will not be translated to shell

    Above everything will have a comment explaining what it does
    
    Not everything can be modified, these instances will be also
    told in the .atrc files
    
    Do not change key or block names

    Whitespace (&) is there for a reason :)

    Variables cannot be redefined nor can their values be changed. 
    They are all constants

    If the program runs into an error, it will log it into console
    and revert back to using the defaults values that have been 
    build in.

    If you want to use reserved chararacters (&, %, !) in values,
    you will need to prefix them with a backslash (\)


ATRC syntax:
    %var%=val   => Variable
    [...]       => Block
    key=val     => Key
    !           => Comment
    %*%         => Insert symbol
    &           => Whitespace symbol
    \           => Prefix symbol

Example file:
    %greeter%=windows
    [messages]
    ! username placed at first Insert
    greeting=Hello %*% from %greeter%\!