package require tdom
 
proc explore {parent} {
    set type [$parent nodeType]
    set name [$parent nodeName]
    
    puts "$parent is a $type node named $name"
    
    if {$type != "ELEMENT_NODE"} then return
    
    if {[llength [$parent attributes]]} {
        puts "attributes: [join [$parent attributes] ", "]"
    }
    
    foreach child [$parent childNodes] {
        explore $child
    }
}
 
proc readTask { filename } {
    set filename "/home/JDuran/simulator/RealTSS/taskSet4.xml";
    set exists [file exists $filename]
    if { $exists > 0 } {
        
            set fd [open $filename]
            set xml_instance [read $fd]
            set doc [dom parse $xml_instance]
            close $fd
            
            
            set root [$doc documentElement]
            
            #set nodeList [$root selectNodes /Taskset/Task/text()]
            
            foreach child [$root childNodes] {
                
                foreach value [$child childNodes] {
                    set name [$value nodeName]
                    set node [$value asText]  ;#  <customer/>
                    
                    puts "name: $name"
                    puts "node: $node"
                }
            }
           
    }   
}

set xml {
    <agents>
        <agent id="007">
            <name type="first">James</name>
            <name type="last">Bond</name>
            <age>Still attractive</age>
            <sex>Male</sex>
        </agent>
        <agent id="013">
            <name type="first">Austin</name>
            <name type="last">Powers</name>
            <age>Depends on your timeline</age>
            <sex>Yes, please</sex>
        </agent>
    </agents>
    }

    readTask $xml
    #set dom [dom parse $xml]
    #set doc [$dom documentElement]
    #puts "Agent: [$doc selectNodes {string(/agents/agent[@id='013']/@id)}]"
    #puts "First Name: [$doc selectNodes {string(/agents/agent[@id='013']/name[@type='first'])}]"
    #puts "Last Name: [$doc selectNodes {string(/agents/agent[@id='013']/name[@type='last'])}]"
    #puts "Age: [$doc selectNodes {string(/agents/agent[@id='013']/age)}]"
    #