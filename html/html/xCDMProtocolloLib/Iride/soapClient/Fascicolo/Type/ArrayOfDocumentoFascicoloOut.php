<?php

namespace IrideWFFascicolo\Type;

class ArrayOfDocumentoFascicoloOut
{

    /**
     * @var \IrideWFFascicolo\Type\DocumentoFascicoloOut
     */
    private $item = null;

    /**
     * @return \IrideWFFascicolo\Type\DocumentoFascicoloOut
     */
    public function getItem()
    {
        return $this->item;
    }

    /**
     * @param \IrideWFFascicolo\Type\DocumentoFascicoloOut $item
     * @return ArrayOfDocumentoFascicoloOut
     */
    public function withItem($item)
    {
        $new = clone $this;
        $new->item = $item;

        return $new;
    }


}

