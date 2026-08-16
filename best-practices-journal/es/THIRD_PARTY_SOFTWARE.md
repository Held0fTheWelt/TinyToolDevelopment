<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Software de terceros

Best Practices Journal no incluye entornos de ejecución de terceros, proveedores de modelos, servidores de bases de datos ni ejecutables externos.

Los flujos de trabajo opcionales con SQLite o Postgres corresponden a perfiles de almacenamiento y opciones del entorno externo. No se distribuyen como software de terceros incluido en el paquete del plugin.

Si un proyecto utiliza SQLite, Postgres, IIS, UCM, UCI, PRS o cualquier otro componente opcional del ecosistema, dicho componente sigue siendo una elección externa del proyecto o del estudio. El paquete distribuido de BPJ debe seguir abriendo, validando, importando, exportando y revisando artefactos JSON sin esos componentes.

Los proveedores y consumidores opcionales son superficies de integración, no software incluido. Su ausencia se reflejará únicamente como estado o diagnóstico, sin provocar fallos de inicio ni errores en el primer uso de BPJ.
