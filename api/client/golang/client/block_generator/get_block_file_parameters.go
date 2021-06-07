// Code generated by go-swagger; DO NOT EDIT.

package block_generator

// This file was generated by the swagger tool.
// Editing this file might prove futile when you re-run the swagger generate command

import (
	"context"
	"net/http"
	"time"

	"github.com/go-openapi/errors"
	"github.com/go-openapi/runtime"
	cr "github.com/go-openapi/runtime/client"
	"github.com/go-openapi/strfmt"
)

// NewGetBlockFileParams creates a new GetBlockFileParams object,
// with the default timeout for this client.
//
// Default values are not hydrated, since defaults are normally applied by the API server side.
//
// To enforce default values in parameter, use SetDefaults or WithDefaults.
func NewGetBlockFileParams() *GetBlockFileParams {
	return &GetBlockFileParams{
		timeout: cr.DefaultTimeout,
	}
}

// NewGetBlockFileParamsWithTimeout creates a new GetBlockFileParams object
// with the ability to set a timeout on a request.
func NewGetBlockFileParamsWithTimeout(timeout time.Duration) *GetBlockFileParams {
	return &GetBlockFileParams{
		timeout: timeout,
	}
}

// NewGetBlockFileParamsWithContext creates a new GetBlockFileParams object
// with the ability to set a context for a request.
func NewGetBlockFileParamsWithContext(ctx context.Context) *GetBlockFileParams {
	return &GetBlockFileParams{
		Context: ctx,
	}
}

// NewGetBlockFileParamsWithHTTPClient creates a new GetBlockFileParams object
// with the ability to set a custom HTTPClient for a request.
func NewGetBlockFileParamsWithHTTPClient(client *http.Client) *GetBlockFileParams {
	return &GetBlockFileParams{
		HTTPClient: client,
	}
}

/* GetBlockFileParams contains all the parameters to send to the API endpoint
   for the get block file operation.

   Typically these are written to a http.Request.
*/
type GetBlockFileParams struct {

	/* ID.

	   Unique resource identifier

	   Format: string
	*/
	ID string

	timeout    time.Duration
	Context    context.Context
	HTTPClient *http.Client
}

// WithDefaults hydrates default values in the get block file params (not the query body).
//
// All values with no default are reset to their zero value.
func (o *GetBlockFileParams) WithDefaults() *GetBlockFileParams {
	o.SetDefaults()
	return o
}

// SetDefaults hydrates default values in the get block file params (not the query body).
//
// All values with no default are reset to their zero value.
func (o *GetBlockFileParams) SetDefaults() {
	// no default values defined for this parameter
}

// WithTimeout adds the timeout to the get block file params
func (o *GetBlockFileParams) WithTimeout(timeout time.Duration) *GetBlockFileParams {
	o.SetTimeout(timeout)
	return o
}

// SetTimeout adds the timeout to the get block file params
func (o *GetBlockFileParams) SetTimeout(timeout time.Duration) {
	o.timeout = timeout
}

// WithContext adds the context to the get block file params
func (o *GetBlockFileParams) WithContext(ctx context.Context) *GetBlockFileParams {
	o.SetContext(ctx)
	return o
}

// SetContext adds the context to the get block file params
func (o *GetBlockFileParams) SetContext(ctx context.Context) {
	o.Context = ctx
}

// WithHTTPClient adds the HTTPClient to the get block file params
func (o *GetBlockFileParams) WithHTTPClient(client *http.Client) *GetBlockFileParams {
	o.SetHTTPClient(client)
	return o
}

// SetHTTPClient adds the HTTPClient to the get block file params
func (o *GetBlockFileParams) SetHTTPClient(client *http.Client) {
	o.HTTPClient = client
}

// WithID adds the id to the get block file params
func (o *GetBlockFileParams) WithID(id string) *GetBlockFileParams {
	o.SetID(id)
	return o
}

// SetID adds the id to the get block file params
func (o *GetBlockFileParams) SetID(id string) {
	o.ID = id
}

// WriteToRequest writes these params to a swagger request
func (o *GetBlockFileParams) WriteToRequest(r runtime.ClientRequest, reg strfmt.Registry) error {

	if err := r.SetTimeout(o.timeout); err != nil {
		return err
	}
	var res []error

	// path param id
	if err := r.SetPathParam("id", o.ID); err != nil {
		return err
	}

	if len(res) > 0 {
		return errors.CompositeValidationError(res...)
	}
	return nil
}