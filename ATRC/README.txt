Notes:
    "Not included" means that the given flag will not be translated to shell

    Above everything will have a comment explaining what it does
    
    Not everything can be modified, these instances will be also
    told in the .atrc files
    
    Do not change key, variable or block names.

    You can switch around inserts

    Whitespace (&) is there for a reason :)

    Variables cannot be redefined nor can their values be changed. 
    They are all constants. You can however make your own variables,
    but the variables' names cannot start with a asterisk (*)

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
    %*[int]%         => Insert symbol
    &           => Whitespace symbol
    \           => Prefix symbol

Example file:
    %greeter%=windows
    [messages]
    ! username placed at first Insert
    greeting=Hello %*% from %greeter%\!
    
    ! Example for numeral inserts.
    ! 0 insert is variable name, 1 insert is flag, 2 insert is question
    command=read %*1% %*2% %*3%
