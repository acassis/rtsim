package require tdom
 
set XML "<orders>
    <order>
        <customer>John Doe</customer>
        <phone>555-4321</phone>
        <email>jdoe@example.com</email>
        <website/>
        <parts>
            <widget sku='XYZ123' />
            <widget sku='ABC789' />
        </parts>
    </order>
    <order>
        <customer>Jane Doe</customer>
        <phone>555-4321</phone>
        <email>jdoe@example.com</email>
        <website/>
        <parts>
            <widget sku='XYZ123' />
            <widget sku='ABC789' />
        </parts>
    </order>
  </orders>"
 set doc [dom parse $XML]
 set root [$doc documentElement]

 # Since there are more than one order nodes a Tcl list will be returned from the selectNodes method.
 set nodeList [$root selectNodes /orders/order/customer/text()]

 # Parse node1 from the returned list.
 set node1 [lindex $nodeList 0]

 # Parse node2 from the returned list.
 set node2 [lindex $nodeList 1]

 # Display there values
 puts [$node1 nodeValue]
 puts [$node2 nodeValue]