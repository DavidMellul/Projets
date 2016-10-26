$(document).ready(function() {
    $("#randomizer").click(function() {  
        var categories = ["famous","movies"];
        var category = categories[Math.round(Math.random())];
        console.log(category);
       $.ajax({
            url: "https://andruxnet-random-famous-quotes.p.mashape.com/",
            type: "GET",
            data: "cat="+category,
            dataType: "json",
            success: function(result) {
                $("#quote").text(result.quote);
                $("#quote").hide();
                $("#quote").fadeIn("slow");

                $("#author").text(result.author);
                $("#author").hide();
                $("#author").fadeIn("slow");
            },
            beforeSend: function(xhr) { 
                xhr.setRequestHeader("X-Mashape-Key", "hVsZjZTUgomshTcGXUPEbXbCZMBHp1OVjFdjsn4ws8JbJElhDm");
            }
        });  
    });
});

