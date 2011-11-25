 package require xml
    package require dom

    set xmlSrc {
        <?xml version="1.0" encoding="UTF-8"?>

        <SampleRequest>
            <PostingURL url="http://foo.com/some/service/url"/>
            <Password>FooBar</Password>
        </SampleRequest>
    }

    # First you parse the XML, the result is held in token d.
    set xmlSrc [string trim $xmlSrc] ;# v2.6 barfed w/o this
    set d [dom::DOMImplementation parse $xmlSrc]

    # One way in is to parse it by the assumed structure and
    # use the Document interface -style of query.  This code isn't
    # flexible at all and only highlights how the dom methods
    # can be used.

    # First find the SampleRequest element in the DOCUMENT
    set sr [set [dom::document getElementsByTagName $d SampleRequest]]

    # Next retrieve the two sub-elements in SampleRequest
    set purl  [set [dom::element getElementsByTagName $sr PostingURL]]
    set pword [set [dom::element getElementsByTagName $sr Password]]

    # Now we will retrieve the url attribute of PostingURL
    set url [dom::element getAttribute $purl url]
    # url == "http://foo.com/some/service/url"
    puts "url = $url"

    # Finally, we want to retrieve the password.  This is non-obvious.
    # The value "FooBar" is actually in a "textNode" child of pword,
    # so you have to do ferret it out with generic node commands.
    set pwordv [dom::node children $pword]
    # You could have also used: dom::node cget $pword -firstchild

    # dom::node cget $pwordv -nodeType  -> textNode
    set password [dom::node cget $pwordv -nodeValue]
    # password == "FooBar"
    puts "password = $password"