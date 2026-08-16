<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Documentación de Best Practices Journal

Best Practices Journal ayuda a los equipos a gobernar prácticas de ingeniería reutilizables directamente dentro de Unreal Editor. Almacena conocimientos sobre prácticas, procedencia, estado de revisión, intención de implementación e historial de resultados bajo una raíz de artefactos local propiedad de BPJ.

La versión 1.1.2 es compatible con Unreal Engine 5.4 y versiones posteriores. Las evidencias importadas y las salidas de proveedores siguen siendo candidatas a revisión hasta su promoción humana explícita; ningún productor externo puede aceptar una práctica de forma autónoma.

BPJ es independiente. Proveedores de ecosistemas opcionales pueden proporcionar evidencias, candidatos, resultados o destinos de entrega, pero el diario, la validación, la búsqueda, la exportación y el ciclo de resultados deben seguir siendo utilizables en ausencia de cualquier proveedor opcional.

## Conceptos principales

- Los registros de prácticas (Practice records) describen guías de ingeniería reutilizables, contexto, compromisos, aplicabilidad, modos de fallo y estado de revisión.
- Los candidatos de práctica (Practice candidates) son borradores o propuestas derivadas de proveedores que aún requieren revisión.
- Los registros de evidencia (Evidence records) conectan prácticas con pruebas locales del proyecto, procedencia, notas de derechos y nivel de confianza.
- Los informes de aplicación (Application briefs) describen la intención de adaptar una práctica revisada a un objetivo específico.
- Las importaciones de resultados (Outcome imports) registran si el trabajo posterior validó, debilitó, contradijo, especializó o reemplazó una práctica.
- Las directivas de redacción y salvaguardas mantienen los registros compartidos de forma controlada.
- Los motores de almacenamiento permiten a BPJ funcionar como artefactos JSON, SQLite local o un perfil de estudio respaldado por Postgres.

## Límite del producto

BPJ es propietario de los registros de prácticas, candidatos, referencias de evidencias, estado de revisión, informes de aplicación, importaciones de resultados de implementación, exportaciones deterministas, validación de esquemas, redacción, salvaguardas e informes locales. No es propietario de la planificación de parches, ejecuciones de prueba/aplicación (dry-run/apply), reversión (rollback), validación final de implementación, ejecución de IA ni modificación de código/activos.

Los informes de aplicación son artefactos de entrega orientados únicamente a la intención. Las herramientas posteriores o flujos de trabajo humanos deben ejecutar sus propios pasos de planificación, aprobación, modificación, validación y reversión.

## Contrato de aceptación

Una práctica aceptada no debe ser un mero eslogan. Antes de la aceptación o reutilización generalizada, registre:

- Problema, contexto y solución.
- Por qué funciona y dónde se aplica.
- Precondiciones, reglas de adaptación, compromisos y modos de fallo.
- Referencias de evidencia, procedencia, notas de derechos y confianza.
- Estado de revisión, notas de revisores e historial de resultados cuando estén disponibles.

Los campos débiles o faltantes deben tratarse como hallazgos de validación, no como inocuos problemas de formato.

## Contrato de informes y resultados

Los informes de aplicación pueden incluir la identidad de la práctica, contexto de destino, adaptación recomendada, restricciones, categorías de acciones permitidas y prohibidas, requisitos de validación, salidas esperadas, referencias de evidencia, estado de aprobación y notas de compatibilidad. No deben incluir código de implementación copiado ni conceder autoridad de modificación.

Las importaciones de resultados actualizan el historial y la confianza en la práctica. Un resultado fallido o rechazado es un dato útil: debe importarse en lugar de ocultarse, ya que puede debilitar, contradecir, especializar o reemplazar la práctica original.

## Artefactos locales y registros

BPJ escribe artefactos locales del proyecto en `Saved/BestPracticesJournal/`, incluyendo `practices`, `candidates`, `evidence`, `application_briefs`, `implementation_outcomes`, `reports`, `schemas`, `logs` y `provider_inbox`. Los diagnósticos de Unreal utilizan `LogBestPracticesJournal`; las pruebas duraderas del operador deben tomarse de los artefactos JSON/Markdown guardados y no de líneas de registro efímeras.

## Documentación para el comprador

- [Guía de inicio rápido](QUICKSTART.md)
- [Manual de usuario](UserManual.md)
- [Referencia de configuración](SettingsReference.md)
- [Solución de problemas](TROUBLESHOOTING.md)
- [Preguntas frecuentes (FAQ)](FAQ.md)
- [Software de terceros](THIRD_PARTY_SOFTWARE.md)
- [Storage Backends](StorageBackends.md)

## Superficies de operación

- Banco de trabajo del editor: crear, revisar, buscar, preparar informes, importar resultados e inspeccionar el estado de integración.
- Artefactos guardados: registros JSON/Markdown en `Saved/BestPracticesJournal/`.
- Commandlets: validación, importación de artefactos y exportación de muestras para automatización y comprobaciones de lanzamiento.
- Rutas/proveedores opcionales: superficies de integración reemplazables que no deben convertirse en requisitos de primer uso.

## Flujos de trabajo

1. Abra `Tools > Best Practices Journal`.
2. Cree o importe registros de prácticas.
3. Adjunte evidencia y estado de revisión.
4. Valide y revise el registro antes de la aceptación.
5. Produzca un informe de aplicación de intención únicamente cuando se conozca el contexto de implementación.
6. Importe resultados tras completar el trabajo posterior.

## Archivos relacionados

- [../README.md](../README.md): inicio rápido.
- [../CHANGELOG.md](../CHANGELOG.md): historial de versiones.
- [StorageBackends.md](StorageBackends.md): modos de almacenamiento JSON, SQLite y Postgres.
