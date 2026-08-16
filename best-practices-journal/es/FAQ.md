<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Preguntas frecuentes (FAQ)

## ¿BPJ es una herramienta genérica de toma de notas?

No. BPJ está diseñado para prácticas de ingeniería respaldadas por evidencias con aplicabilidad, compromisos, modos de fallo, procedencia, estado de revisión e historial de resultados.

## ¿Cuándo debe mantenerse algo como candidato?

Manténgalo como candidato cuando la evidencia, aplicabilidad, compromisos, modos de fallo, procedencia o estado de revisión estén incompletos. Los candidatos son útiles, pero no deben tratarse como directrices aceptadas.

## ¿BPJ modifica los archivos del proyecto?

No. BPJ puede generar informes de aplicación e importar resultados, pero la modificación del proyecto corresponde a herramientas posteriores aprobadas o a flujos de trabajo humanos.

## ¿Qué debe incluirse en un informe de aplicación?

Utilice el informe para el contexto de destino, adaptación recomendada, restricciones, referencias de evidencia, validación requerida y estado de aprobación. No lo utilice como plan de parches ni comando de modificación.

## ¿BPJ requiere IIS, SDA, UCI, PRS, UCM o LLM Store?

No. BPJ es independiente. Plugins opcionales de Tiny Tool pueden proporcionar evidencias, indexación, documentación, implementación o flujos de rutas, pero no son necesarios para el uso principal.

## ¿BPJ puede llamar a la IA o decidir pasos de implementación?

No. BPJ puede almacenar evidencias o intenciones creadas por otro flujo de trabajo revisado, pero no es propietario de la ejecución de IA, búsqueda, planificación de parches, aplicación, reversión ni validación final.

## ¿Dónde se almacenan los datos?

El perfil predeterminado utiliza artefactos JSON locales del proyecto en la raíz de almacenamiento de BPJ. Se pueden configurar perfiles opcionales en SQLite o perfiles externos de estudio para flujos de mayor escala.

## ¿Qué datos pueden ser confidenciales?

Los registros de prácticas, evidencias, informes, resultados e informes en general pueden contener rutas locales, nombres de proyectos, notas de revisión, salidas de validación, notas de derechos o diagnósticos de proveedores. Revise y redacte (censure) las exportaciones antes de compartirlas.

## ¿Dónde encuentro los registros e informes?

Los informes se guardan en `Saved/BestPracticesJournal/reports/`. Los diagnósticos de tiempo de ejecución, del editor y de commandlets utilizan `LogBestPracticesJournal` en el registro de Unreal. Los artefactos guardados son la prueba duradera.

## ¿Puedo compartir prácticas con un equipo?

Sí, tras su revisión. Trate las exportaciones como locales del proyecto hasta que hayan sido depuradas de rutas privadas, notas confidenciales y evidencias con derechos protegidos.

## ¿La falta de proveedores opcionales puede dañar el diario?

No. Los proveedores ausentes solo deben mostrarse como estado o diagnóstico. Los registros manuales, evidencias locales, validación, exportación e importación de resultados deben seguir estando disponibles.

## ¿Deben importarse los resultados fallidos?

Sí. Los resultados fallidos, rechazados, parciales y sin efecto (no-op) son importantes porque pueden debilitar, contradecir, especializar o reemplazar la práctica. Ocultarlos resta credibilidad al diario.
