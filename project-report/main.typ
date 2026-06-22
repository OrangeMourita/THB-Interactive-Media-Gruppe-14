#import "@preview/ilm:2.1.1": *

#set text(lang: "de")

#show: ilm.with(
  title: [Projektbericht \ #emph[Leafy Listener]],
  authors: ("Hannes Segebarth", "Jordan Zangio Kitio", "Konstantin Gernert", "Manuel Knappik", "Moritz Grünberg"),
  abstract: [#lorem(30)],
  bibliography: [],
  figure-index: (enabled: true),
  table-index: (enabled: true),
  listing-index: (enabled: true),
  date: none
)




= Konzept
== Foobar
#lorem(500)



= System Design & Implementierung
#lorem(500)


= Evaluation
#lorem(500)


= Conclusio
#lorem(500)

= Bibliographie
#bibliography("biblatex-examples.bib", full: true, style: "apa", title: none)