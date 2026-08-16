<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Manual de usuario

Best Practices Journal es un banco de trabajo del editor para la gobernanza de prácticas de ingeniería respaldadas por evidencias. Es un soporte para la toma de decisiones y una memoria de revisión, no un planificador de parches, editor de código fuente, ejecutor de IA ni herramienta de modificación de activos.

## Flujo de trabajo principal

1. Capture una práctica o candidato desde una nota manual, referencia de evidencia o proveedor opcional.
2. Añada aplicabilidad, compromisos, modos de fallo, procedencia, notas de derechos y metadatos de revisión.
3. Valide el registro antes de aceptarlo o exportarlo.
4. Busque prácticas al seleccionar directrices para una tarea o revisión.
5. Cree un informe de aplicación para una práctica revisada o candidato explícito.
6. Entregue el informe a un flujo de trabajo humano, UCI, PRS u otro ejecutor aprobado.
7. Importe informes de resultados de implementación para registrar si la práctica fue validada, debilitada, contradicha, especializada o reemplazada.

## Calidad de los registros de prácticas

Utilice BPJ para prácticas capaces de superar una revisión. Un registro útil incluye:

- Un problema concreto y un contexto de destino.
- Una solución formulada como guía reutilizable, no como código de implementación copiado.
- Por qué funciona la guía, dónde se aplica y dónde falla.
- Compromisos, precondiciones, reglas de adaptación y modos de fallo.
- Referencias de evidencia, procedencia, notas de derechos, confianza y estado de revisión.

Si desconoce estos campos, mantenga el elemento como candidato o borrador. No lo promueva a directriz aceptada solo porque el resumen parezca plausible.

## Operaciones públicas

- **Create practice record** almacena una práctica revisada o borrador con evidencias, contexto, compromisos y estado de revisión.
- **Create practice candidate** almacena un borrador o propuesta derivada de un proveedor hasta que se revise explícitamente.
- **Attach evidence** vincula pruebas locales/manuales/del proveedor sin copiar código de implementación restringido.
- **Search practices** devuelve registros de prácticas coincidentes del almacén de artefactos propiedad de BPJ.
- **Create application brief** exporta una entrega orientada únicamente a la intención para un contexto de destino específico.
- **Import implementation outcome** cierra el ciclo tras la implementación o el rechazo.

## Informes de aplicación (Application Briefs)

Un informe debe ayudar a otro flujo de trabajo a planificar con seguridad. Puede incluir proyecto/módulo/alcance de destino, adaptación recomendada, justificación, restricciones, categorías de acciones permitidas y prohibidas, requisitos de validación, salidas esperadas, referencias de evidencia, estado de aprobación y notas de compatibilidad.

Un informe no debe actuar como permiso para que BPJ modifique archivos. Si la herramienta posterior aplica cambios, debe asumir la resolución del alcance, la planificación de simulaciones, la aprobación, los controles de modificación, la validación, la reversión y su propio informe de resultados.

## Importaciones de resultados (Outcome Imports)

Importe todos los resultados significativos, incluidos los fallidos, rechazados, parciales y sin efecto (no-op). Los resultados actualizan el historial de la práctica, la confianza, las notas de revisión y los enlaces de evolución. No reescriben la práctica original como universalmente correcta.

Utilice los campos de resultados para referencias a archivos modificados, rutas de informes de validación, lecciones aprendidas, actualizaciones recomendadas del diario, advertencias, errores y enlaces a planes o informes externos.

## Proveedores opcionales

Proveedores opcionales de evidencia, candidatos, resultados, entregas, indexación, rutas o implementación pueden enriquecer BPJ. Deben seguir siendo reemplazables. Si falta un proveedor, continúe con registros manuales, evidencias locales, artefactos JSON/Markdown y validación de BPJ.

## Capability Mesh (MCP)

Los agentes sin acceso a archivos pueden cerrar el ciclo de vida del diario centrado en revisiones a través de UMCP:

- `bpj.gather_candidates.v1` — examina las carpetas de la bandeja de entrada de proveedores (incluido `project_intelligence_orchestrator` de la entrega PIO).
- `bpj.repository.list.v1` — enumera los ID de prácticas, candidatos, evidencias, informes y resultados.
- `bpj.practice.read.v1` — lee directamente un registro serializado.
- `bpj.candidate.promote.v1` — promueve un candidato revisado (requiere aprobación del usuario en la ruta).
- `bpj.import_artifacts.v1` — importa sobres de candidatos PIO (`schema` / `schema_version` que comiencen por `bpj.implementation_intent_candidates.`).

Ruta de la bandeja de entrada del proveedor: `Saved/BestPracticesJournal/provider_inbox/candidates/<provider_id>/`.

## Commandlets

Los commandlets son útiles para la validación, importación de artefactos y exportación de muestras, pero no son pasos obligatorios para el primer uso. Utilice los informes guardados en `Saved/BestPracticesJournal/reports/` como evidencias duraderas para la automatización. Los registros resumen lo sucedido; los artefactos guardados siguen siendo el registro oficial.

## Límites

BPJ registra conocimientos e intenciones. No modifica archivos fuente, activos, archivos Build.cs, descriptores de proyecto ni código de plugins externos. Los responsables de ejecución posteriores deben aplicar sus propios controles de vista previa, aprobación, validación y reversión.

## Evidencias locales y registros

BPJ almacena evidencias duraderas de revisión en `Saved/BestPracticesJournal/`. Utilice los archivos JSON/Markdown en `reports`, `application_briefs`, `implementation_outcomes` y `schemas` al compartir o auditar un flujo de trabajo. La categoría de registro de Unreal `LogBestPracticesJournal` se utiliza para diagnósticos del operador y resúmenes de commandlets; no es el registro oficial de prácticas aceptadas.
