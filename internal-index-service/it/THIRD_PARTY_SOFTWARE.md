<!-- doc-provenance: SAD architecture.md sections 2,7,8; facts product-facts.yml; reconciled 2026-07-16 -->
# Software di terze parti

Internal Index Service include il seguente codice sorgente di terze parti. Contrassegna l'invio del plugin come contenente software di terze parti e includi questa voce nel modulo di dichiarazione dei software di terze parti di Epic.

| Software | Versione | Licenza | Fonte | Percorso nel plugin | Utilizzo |
| --- | --- | --- | --- | --- | --- |
| hnswlib | 0.9.0 | Apache License 2.0 | https://github.com/nmslib/hnswlib | `Source/ThirdParty/hnswlib` | Backend per l'indice dei vicini più prossimi approssimati vettoriale locale in C++ (solo header). |

Il plugin confezionato include i file originali `LICENSE` e `NOTICE.md` nella cartella `Source/ThirdParty/hnswlib`.
